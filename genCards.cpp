#include <iostream>
using namespace std;

void shift(int* costs, int* resource, int i)
{
  int temp = costs[0];
  for (int j = 0; j < 4; j++)
  {
    costs[j] = costs[j+1];
    if (j == i) {
      resource[j] = 1;
    }
    else
      resource[j] = 0;
  }
  if (i == 4) {
    resource[4] = 1;
  }
  else
    resource[4] = 0;
  costs[4] = temp;
}

int main()
{
	int costs[5];
	int resource[5];
	/*
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
      			if (i == j) {
        			costs[j] = 0;
        			resource[j] = 1;
      			}
      			else if (j == i + 1) {
       				costs[j] = 2;
      			}
			else if (j == 0 && i == 4)
			{
				costs[j] = 2;
			}		
      			else {
        			costs[j] = 1;
        			resource[j] = 0;
      			}
			
			cout << costs[j] << " ";
    		}
		cout << endl;
	}
	*/
	costs[0] = 2;
	costs[1] = 1;
	costs[2] = 0;
	costs[3] = 2;
	costs[4] = 0;

	for (int i = 0; i < 5; i++)
	{
		cout << costs[i] << " ";
	}
	cout << endl;
	
	for (int i = 0; i < 4; i++) {
		shift(costs, resource, i);
		for (int r = 0; r < 5; r++)
		{
			cout << costs[r] << " ";
		}
			cout << endl;
	}
}
