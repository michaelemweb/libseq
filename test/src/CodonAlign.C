#include <fstream>
#include <stdlib.h>

#include "CodonAlign.h"
#include "NeedlemanWunsh.h"
#include "AlignmentAlgorithm.h"

using namespace seq;

int main(int argc, char **argv)
{
  std::ifstream s1(argv[1]);
  std::ifstream s2(argv[2]);
  
  int frameshifts;
  if(argc > 3)
    frameshifts = atoi(argv[3]);
  else
    frameshifts = 5;

  NTSequence seq1, seq2;
  s1 >> seq1;
  s2 >> seq2;

  try {
    AlignmentAlgorithm* needlemanWunsh = new NeedlemanWunsh(-10, -3.3);
//    needlemanWunsh->align(seq1,seq2);

    CodonAlign codonAlign(needlemanWunsh);
    std::pair<double, int> result = 
      codonAlign.align(seq1, seq2, frameshifts);

    std::cerr << "Aligned successfully, score: " << result.first
	      << ", frameshifts: " << result.second << std::endl;

    std::cerr << seq1 << seq2 << std::endl;
  } catch (std::exception& e) {
    std::cerr << "Alignment problem: " << e.what() << std::endl;
  }

  return 0;
}
