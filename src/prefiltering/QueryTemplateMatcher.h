#ifndef QUERY_TEMPLATE_MATCHER_H
#define QUERY_TEMPLATE_MATCHER_H

#include <list>
#include <iostream>
#include <cstring>


#include "../commons/BaseMatrix.h"
#include "../commons/Sequence.h"
#include "ExtendedSubstitutionMatrix.h"
#include "QueryScore.h"
#include "IndexTable.h"
#include "KmerGenerator.h"
#include "Indexer.h"


class QueryTemplateMatcher {
    public:
        QueryTemplateMatcher (BaseMatrix* m,
                ExtendedSubstitutionMatrix* _2merSubMatrix,
                ExtendedSubstitutionMatrix* _3merSubMatrix,
                IndexTable * indexTable,
                unsigned short * seqLens,
                short kmerThr,
                double kmerMatchProb,
                int kmerSize,
                int dbSize,
                bool aaBiasCorrecion,
                int maxSeqLen,
                float zscoreThr); 

        ~QueryTemplateMatcher();
        // returns result for the sequence
        std::list<hit_t>*  matchQuery (Sequence * seq);
        // returns result for the sequence, using the reverse sequence statistics for result caluclation
        std::list<hit_t>*  matchQueryRevSeq (Sequence * seq);
        // calculate local amino acid bias correction score for each position in the sequence
        void calcLocalAaBiasCorrection(Sequence* seq);

    private:
        // match sequence against the IndexTable
        void match(Sequence* seq, void (QueryScore::*addScores)(int* seqList, int seqListSize, short score));
        // scoring matrix for local amino acid bias correction
        BaseMatrix * m;
        /* generates kmer lists */
        KmerGenerator * kmerGenerator;
        /* contains the sequences for a kmer */
        IndexTable * indexTable;
        /* calculates the score */
        QueryScore * queryScore;
        // k of the k-mer
        int kmerSize;
        // local amino acid bias correction
        bool aaBiasCorrection;
        // local score correction values
        float* deltaS;

};

#endif