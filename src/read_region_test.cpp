// ==========================================================================
//                              read_region_test
// ==========================================================================
// Copyright (c) 2006-2013, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: Your Name <your.email@example.net>
// ==========================================================================

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include <seqan/stream.h>

using namespace std;

int main(int argc, char const ** argv)
{
    if (argc != 5)
    {
        std::cerr << "USAGE: read_region REFERENCE_FILE.fa CHROMOSOME_NUMBER START_POSITION END_POSITION \n";
        return 1;
    }

	// Try to load index and create on the fly if necessary.
	seqan::FaiIndex faiIndex;
    if (seqan::read(faiIndex, argv[1]) != 0)
    {
        if (build(faiIndex, argv[1]) != 0)
        {
            std::cerr << "ERROR: Index could not be loaded or built.\n";
            return 1;
        }
        if (write(faiIndex) != 0)  // Name is stored from when reading.
        {
            std::cerr << "ERROR: Index could not be written do disk.\n";
            return 1;
        }
    }

    // Translate sequence name to index.
    unsigned idx = 0;
    if (!getIdByName(faiIndex, argv[2], idx))
    {
        std::cerr << "ERROR: Index does not know about sequence " << argv[2] << "\n";
        return 1;
    }

    // Finally, get infix of sequence.
    seqan::Dna5String sequenceInfix;
    if (readRegion(sequenceInfix, faiIndex, idx, strtoul(argv[3],NULL, 0), strtoul(argv[4],NULL,0)) != 0)
    {
        std::cerr << "ERROR: Could not load infix.\n";
        return 1;
    }

	//stringstream seqStr;
	//seqStr<<sequenceInfix;

	cout<<sequenceInfix<<endl;

    return 0;
}
