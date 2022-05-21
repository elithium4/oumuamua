#include "Observation.h"

#include "Facade.h"
#include "Matrix.h"


int main(){
    Facade f;
    /*f.read_data();
    f.convert_observations();
    f.convert_observatory();
    f.integrate();
    f.test_reading();*/
    Matrix a(3, 3, {{1, 2, 5},
                    {3, 4, 6},
                    {3, 4, 5}});
    
    Matrix b(3, 2, {
        {3, 2},
        {4, 1},
        {2, 5}
    });

    std::cout<<a;

    Matrix c(2, 2);
    c = (a*b);
    std::cout<<c;

    Matrix G(6, 6);

    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            G[i][j] = 9;
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            G[i][j] = 0;
            G[6-i - 1][6-j-1] = 0;
            G[i][j+3] = 0;
            if (j == i){
                G[i][j+3] = 1;
            }
        }
    }

    std::cout<<G;

    return 0;
}