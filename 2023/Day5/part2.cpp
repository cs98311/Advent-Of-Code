#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <vector>

// VECtor Of VECtors
typedef std::vector<std::vector<long int>> vecovec;

// Nx2 matrix containing seed ranges
void make_seeds(vecovec *vec);

// Mx3 matrix containing maps
void make_vector(vecovec *vec);

// function to sort a VecOVec acc. to given index of inner vectors
void sort_vecovec(vecovec *vec, size_t index);

// find overlaps, apply conversions and store in new vectors
// no reductions in ranges here
void overlap(vecovec *v1, vecovec *v2, vecovec *newvec);

int main() {

  // Declaring v1 arrays
  // Nx2 vecovecs to contain ranges of seeds, soils, etc
  vecovec seeds;
  vecovec soil;
  vecovec fert;
  vecovec water;
  vecovec light;
  vecovec temp;
  vecovec humid;
  vecovec loc;

  // Declaring v2 arrays
  // Mx3 vecovecs to contain conversion maps
  vecovec seed2soil;
  vecovec soil2fert;
  vecovec fert2water;
  vecovec water2light;
  vecovec light2temp;
  vecovec temp2humid;
  vecovec humid2loc;

  // Creating Nx2 vecovec for seeds ranges
  make_seeds(&seeds);

  // Creating Mx3 maps
  make_vector(&seed2soil);
  make_vector(&soil2fert);
  make_vector(&fert2water);
  make_vector(&water2light);
  make_vector(&light2temp);
  make_vector(&temp2humid);
  make_vector(&humid2loc);

  // Sorting vevecs by index
  sort_vecovec(&seeds, 0);
  sort_vecovec(&seed2soil, 1);
  sort_vecovec(&soil2fert, 1);
  sort_vecovec(&fert2water, 1);
  sort_vecovec(&water2light, 1);
  sort_vecovec(&light2temp, 1);
  sort_vecovec(&temp2humid, 1);
  sort_vecovec(&humid2loc, 1);

  // Checking Overlaps
  overlap(&seeds, &seed2soil, &soil);
  overlap(&soil, &soil2fert, &fert);
  overlap(&fert, &fert2water, &water);
  overlap(&water, &water2light, &light);
  overlap(&light, &light2temp, &temp);
  overlap(&temp, &temp2humid, &humid);
  overlap(&humid, &humid2loc, &loc);

  // find the minimum of the starts of the ranges in loc
  long int minimum{loc[0][0]};
  for (auto i : loc) {
    if (i[0] < minimum) {
      minimum = i[0];
    }
  }
  std::cout << "Minimum : " << minimum << std::endl;

  return 0;
}

// FUNCTIONS

// take first line of input and extract seed ranges in a Nx2 vecovec
void make_seeds(vecovec *vec) {
  std::string sentence;
  std::clog << "Enter the input" << std::endl;
  // continue getting lines from input
  while (std::getline(std::cin, sentence)) {
    // until empty line encountered
    if (sentence == " " || sentence == "") {
      break;
    }
    // if seeds: found in the sentence
    else if (sentence.find("seeds:") != std::string::npos) {
      std::vector<std::string> words;
      // split with empty space as delimiter and store in vector 'words'
      boost::split(words, sentence, boost::is_any_of(" "),
                   boost::token_compress_on);
      // convert string to long int and push pair of range to a vecovec
      for (unsigned long int i = 1; i < words.size(); i += 2) {
        std::vector<long int> pair;
        pair.push_back(stol(words[i]));
        pair.push_back(stol(words[i + 1]));
        // pair.push_back(stol(words[i]) + stol(words[i + 1]) - 1);
        vec->push_back(pair);
      }
    }
  }
}

// make vecovec for conversion maps
void make_vector(vecovec *vec) {
  std::string sentence;
  while (std::getline(std::cin, sentence)) {
    if (sentence == " " || sentence == "") {
      break;
    } else if (sentence[sentence.length() - 1] == ':') {
      continue;
    } else {
      std::vector<std::string> words;
      boost::split(words, sentence, boost::is_any_of(" "),
                   boost::token_compress_on);
      std::vector<long int> v;
      v.push_back(stol(words[0]));
      v.push_back(stol(words[1]));
      v.push_back(stol(words[2]));

      vec->push_back(v);
    }
  }
}

// sort vecovec acc to index of inner vectors
void sort_vecovec(vecovec *vec, size_t index) {
  std::sort(
      vec->begin(), vec->end(),
      [index](const std::vector<long int> &a, const std::vector<long int> &b) {
        return a[index] < b[index];
      });
}

void overlap(vecovec *v1, vecovec *v2, vecovec *newvec) {
  // v1 is Nx2 ranges and v2 is Mx3 map
  // newvec is the Nx2 vecovec filled based on overlaps and conversions

  for (auto i = 0UL; i < v1->size(); i++) {
    long int v1_start{v1->at(i)[0]};
    long int v1_range{v1->at(i)[1]};
    long int v1_end{v1_start + v1_range - 1};

    // since v2 has continuous range
    long int v2_smallest{v2->at(0)[1]};
    long int v2_largest{v2->at(v2->size() - 1)[1] + v2->at(v2->size() - 1)[2] -
                        1};
    // if v1[i] completely outside v2 range
    if (v1_start > v2_largest || v1_end < v2_smallest) {
      // push v1[i] as it is
      std::vector<long int> temp;
      temp.push_back(v1_start);
      temp.push_back(v1_range);
      newvec->push_back(temp);
      continue;
    }
    // if v1[i] has partial overlap at v2 's beginning
    else if (v1_start < v2_smallest && v1_end >= v2_smallest) {
      // push the outside part as it is
      std::vector<long int> temp;
      temp.push_back(v1_start);
      temp.push_back(v2_smallest - v1_start);
      newvec->push_back(temp);
    }
    // if v1[i] has partial overlap at v2 's end
    else if (v1_start <= v2_largest && v1_end > v2_largest) {
      // push the outside part as it is
      std::vector<long int> temp;
      temp.push_back(v2_largest + 1);
      temp.push_back(v1_end - v2_largest);
      newvec->push_back(temp);
    }
    // deal with any overlaps now
    for (auto j = 0UL; j < v2->size(); j++) {
      // conversion factor of v2[j]
      long int conversion_factor{v2->at(j)[0] - v2->at(j)[1]};
      long int v2_start{v2->at(j)[1]};
      long int v2_range{v2->at(j)[2]};
      long int v2_end{v2_start + v2_range - 1};

      // if end of v1[i] is less than start of a v2[j]
      // break because v2 is sorted and will get bigger
      if (v1_end < v2_start) {
        break;
      }

      // if start of v1[i] is greater than v2[j] skip to next j
      // since v2 is sorted
      else if (v1_start > v2_end) {
        continue;
      }

      // if v1[i] overlaps with v2[j]
      else {
        long int overlap_start{std::max(v1_start, v2_start)};
        long int overlap_end{std::min(v1_end, v2_end)};
        long int overlap_range{overlap_end - overlap_start + 1};

        // create a temporary vector to then push into the vecovec
        std::vector<long int> temp;
        temp.push_back(overlap_start + conversion_factor);
        temp.push_back(overlap_range);
        newvec->push_back(temp);
      }
    }
  }
}

