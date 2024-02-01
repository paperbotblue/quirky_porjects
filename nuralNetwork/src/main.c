#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] =
        {
            {0,0},
            {1,1},
            {2,2},
            {3,3},
            {4,4},
            {5,5},
            {6,6}
        };

//y = x*W;

#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float()
{
    return (float)rand()/(float)RAND_MAX;
}

float cost(float w)
{
    float result = 0.0f ;
    for(size_t i = 0; i < train_count ; ++i)
    {
        float x = train[i][0];
        float y = x*w;
        float d = y - train[i][1];
        result+=d*d;
    }
    result/=train_count;
    return result;
}

int main()
{
    srand(time(0));
    float age;
    float accuracy;
    printf("Enter your age:");
    scanf("%f",&age);

    float w = rand_float()*10.0f;
    
    float eps = 1e-3;
    float rate = 1e-3; 

    for(int i = 0; i < 500 ; ++i)
    {
        float c = cost(w);
        float dw = (cost(w+eps) - c)/eps;
        w-=rate*dw;
        printf("cost: %f, w: %f\n",cost(w),w);
    }

    printf("------------------\n");
    printf("final multipiler: %f\n",w);
    if(w>1.0)
    {
        accuracy = 100.0-(w-1.0);
        printf("Expected accuracy is: %f\n",accuracy);
    }
    else
    {
        printf("Expected accuracy is: %f\n",(age*w/age)*100.0);
    }
    printf("Your aprox age is: %f\n",age*w);
    return 0;

}   

//39:25