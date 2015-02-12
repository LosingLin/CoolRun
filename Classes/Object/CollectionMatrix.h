//
//  CollectionMatrix.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef CoolRun_CollectionMatrix_h
#define CoolRun_CollectionMatrix_h

struct CollectionMatrix6X6
{
    int matrix[6][6];
}*CollectionMatrix6X6_PTR;

namespace CollectionMatrixInstance
{
    CollectionMatrix6X6 ZERO = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    }};
    CollectionMatrix6X6 ONE = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {1,1,1,1,1,1}
    }};
    CollectionMatrix6X6 TWO = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {1,1,1,1,1,1}
    }};
    CollectionMatrix6X6 THREEN = {{
        {0,1,1,1,1,0},
        {1,1,0,0,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,0,0,1,1},
        {0,1,1,1,1,0}
    }};
    CollectionMatrix6X6 FOUR = {{
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    }};
    CollectionMatrix6X6 FIVE = {{
        {0,0,0,0,0,0},
        {0,0,0,0,1,1},
        {0,0,0,1,1,0},
        {0,0,1,1,0,0},
        {0,1,1,0,0,0},
        {1,1,0,0,0,0}
    }};
    CollectionMatrix6X6 SIX = {{
        {0,0,0,0,0,0},
        {1,1,0,0,0,0},
        {0,1,1,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,1,1,0},
        {0,0,0,0,1,1}
    }};
    
    CollectionMatrix6X6 INSTANCE[] = {
        ZERO, ONE, TWO, THREEN, FOUR, FIVE, SIX
    };
    
};

#endif
