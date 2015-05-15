//
//  CollectionMatrix.h
//  CoolRun
//
//  Created by ManYou on 14-10-7.
//
//

#ifndef CoolRun_CollectionMatrix_h
#define CoolRun_CollectionMatrix_h

#define kCollectionMatrixNum 6

struct CollectionMatrix
{
    int matrix[kCollectionMatrixNum][kCollectionMatrixNum];
}*CollectionMatrix_PTR;

namespace CollectionMatrixInstance
{
    CollectionMatrix ZERO = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {1,0,0,0,0,0}
    }};
    CollectionMatrix ONE = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {1,1,1,1,1,1}
    }};
    CollectionMatrix TWO = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {1,1,1,1,1,1}
    }};
    CollectionMatrix THREEN = {{
        {0,1,1,1,1,0},
        {1,1,0,0,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,0,0,1,1},
        {0,1,1,1,1,0}
    }};
    CollectionMatrix FOUR = {{
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    }};
    CollectionMatrix FIVE = {{
        {0,0,0,0,0,0},
        {0,0,0,1,1,0},
        {0,0,1,1,0,0},
        {0,1,1,0,0,0},
        {1,1,0,0,0,0},
        {0,0,0,0,0,0}
    }};
    CollectionMatrix SIX = {{
        {0,0,0,0,0,0},
        {0,1,1,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,1,1,0},
        {0,0,0,0,1,1},
        {0,0,0,0,0,0}
    }};
    CollectionMatrix SEVEN = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,1,0,0,0},
        {0,1,1,1,0,0},
        {1,1,1,1,1,0}
    }};
    CollectionMatrix EIGHT = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1}
    }};
    CollectionMatrix NINE = {{
        {0,1,0,0,1,0},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {0,1,1,1,1,0},
        {0,0,1,1,0,0},
        {0,0,0,0,0,0}
    }};
    CollectionMatrix TEN = {{
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1}
    }};
    CollectionMatrix ELEVEN = {{
        {0,0,1,1,0,0},
        {0,1,1,1,1,0},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {0,1,1,1,1,0},
        {0,0,1,1,0,0}
    }};
    CollectionMatrix TWELVE = {{
        {0,0,1,0,0,0},
        {0,1,1,1,0,0},
        {1,0,1,0,1,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,0,0,0}
    }};
    CollectionMatrix THIRTEEN = {{
        {0,0,0,1,0,0},
        {0,0,0,0,1,0},
        {0,1,1,1,1,1},
        {0,0,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,0,0,0,0}
    }};
    CollectionMatrix FOURTEEN = {{
        {0,0,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {1,0,1,0,1,0},
        {0,1,1,1,0,0},
        {0,0,1,0,0,0}
    }};
    CollectionMatrix FIFTEEN = {{
        {0,0,1,0,0,0},
        {0,1,0,0,0,0},
        {1,1,1,1,1,0},
        {0,1,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,0,0,0}
    }};
    
    CollectionMatrix INSTANCE[] = {
        ZERO, ONE, TWO, THREEN, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN,
        TWELVE, THIRTEEN, FOURTEEN, FIFTEEN
    };
    
};

#endif
