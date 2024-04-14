#include<bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;
void printOut(int frames[], int needed, int capacity){
    cout.width(2);
    cout.fill('0');
    cout << needed << "     ";
    for(int i =0; i < capacity; i++)
    {
        if(frames[i]==-1)
            break;
        cout.width(2);
        cout.fill('0');
        cout << frames[i] << " ";
    }
    cout << "-------------------------------------";
    cout << "\n";
}

int findInArray(int frames[], int number, int capacity)
{
    int flag = 0;

    for(int i = 0; i<capacity ;i++)
    {
        if(frames[i] == number)
            flag = 1 ;
    }
    return flag;
}

int findInArrayIndex(int frames[], int number, int capacity)
{
    int index = -1;
    for(int i = 0; i < capacity ;i++)
    {
            if(frames[i] == number){
            index = i ;
            break;
            }
    }
    return index;
}

int findMinIndex(int occurrence[],int capacity)
{
    int minimum=occurrence[0];

    for(int i = 1; i < capacity; i++){
        if(minimum > occurrence[i])
            minimum = occurrence[i];
    }

    int minIndex = findInArrayIndex(occurrence,minimum,capacity);
    return minIndex;
}


int findMaxIndex(int occurrence[],int capacity)
{
    int maximum = occurrence[0];
    int maxIndex = -1;

    for(int i = 1; i < capacity; i++){
        if(maximum < occurrence[i])
            maximum = occurrence[i];
    }

    if(findInArray(occurrence,-1,capacity))
        maxIndex = findInArrayIndex(occurrence,-1,capacity);
    else maxIndex = findInArrayIndex(occurrence,maximum,capacity);
    return maxIndex;
}

int findReplaceIndex(int frames[], int pages[], int pageSize, int capacity, int startIndex)
{
    int occurrence[capacity];
    for(int i = 0; i < capacity; i++)
    {
        occurrence[i] = -1;
    }
    for(int i = 0; i < capacity ; i++)
    {
        for(int j = startIndex; j < pageSize ; j++){
            if(frames[i] == pages[j])
            {
                occurrence[i] = j;
                cout << "occurrence of" << frames[i] << "at pages index" << j << "\n";
                break;
            }
        }
    }

    int replaceIndex = findMaxIndex(occurrence,capacity);
    return replaceIndex;
}

int OPTIMAL(int pages[], int n, int capacity){
    cout << "Replacement Policy = OPTIMAL\n";
    cout << "-------------------------------------\n";
    cout << "Page   Content of Frames\n";
    cout << "---    -----------------\n";

    int frames[capacity];
    for(int i = 0; i<capacity; i++)
    {
        frames[i] = -1;
    }

    int faults = 0, j = 0, full = 0;

    for(int i = 0; i < n; i++)
    {
         if (full < capacity)
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                frames[j] = pages[i];
                full++;
                j++;
                j = j % capacity;
                printOut(frames,pages[i],capacity);
            }
             else{
                printOut(frames,pages[i],capacity);
            }
        }
        else
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                int startIndex = i+1;
                int replacedIndex = findReplaceIndex(frames,pages,n,capacity,startIndex);
                frames[replacedIndex] = pages[i];
                j++;
                j = j % capacity;
                cout.width(2);
                cout.fill('0');
                cout << pages[i] << " F   " ;
                for(int k = 0; k < capacity; k++)
                {
                cout.width(2);
                cout.fill('0');
                cout << frames[k] << " ";
                }
                cout << "\n";
                faults++;
            }
            else{
              printOut(frames,pages[i],capacity);
            }
        }
    }
    return faults;
}

int LRU(int pages[], int n, int capacity){
    cout << "Replacement Policy = LRU\n";
    cout << "-------------------------------------\n";
    cout << "Page    Content of Frames\n";
    cout << "---     -----------------\n";

    int frames[capacity], occurrence[capacity];
    for(int i = 0; i<capacity; i++)
    {
        frames[i] = -1;
    }
    for(int i = 0; i<capacity; i++)
    {
        occurrence[i] = -1;
    }

    int faults = 0, j = 0, full = 0;

    for(int i = 0; i < n; i++)
    {
         if (full < capacity)
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                frames[j] = pages[i];
                occurrence[j]=i;
                full++;
                j++;
                j = j % capacity;
                printOut(frames,pages[i],capacity);
            }
             else{
                int foundIndex = findInArrayIndex(frames,pages[i],capacity);
                occurrence[foundIndex] = i;
                printOut(frames,pages[i],capacity);
            }
        }
        else
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                int minIndex = findMinIndex(occurrence,capacity);
                frames[minIndex] = pages[i];
                occurrence[minIndex] = i;
                j++;
                j = j % capacity;
                cout.width(2);
                cout.fill('0');
                cout << pages[i] << " F    " ;
                for(int k = 0; k < capacity; k++)
                {
                cout.width(2);
                cout.fill('0');
                cout << frames[k] << " ";
                }
                cout << "\n";
                faults++;
            }
            else{
              int foundIndex = findInArrayIndex(frames,pages[i],capacity);
              occurrence[foundIndex] = i;
              printOut(frames,pages[i],capacity);
            }
        }
    }
    return faults;
}

int CLOCK(int pages[], int n, int capacity){
    cout << "Replacement Policy = CLOCK\n";
    cout << "-------------------------------------\n";
    cout << "Page    Content of Frames\n";
    cout << "---     -----------------\n";

    int frames[capacity], occurrence[capacity];
    for(int i = 0; i<capacity; i++)
    {
        frames[i] = -1;
    }
    for(int i = 0; i<capacity; i++)
    {
        occurrence[i] = 0;
    }
    int faults = 0, j = 0, full = 0;

    for(int i = 0; i < n; i++)
    {
         if (full < capacity)
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                frames[j] = pages[i];
                occurrence[j]=1;
                full++;
                j++;
                j = j % capacity;
                printOut(frames,pages[i],capacity);
            }
             else{
                int editedIndex = findInArrayIndex(frames,pages[i],capacity);
                occurrence[editedIndex] = 1;
                printOut(frames,pages[i],capacity);
            }
        }
        else
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                while(!findInArray(frames,pages[i],capacity)){
                    if(occurrence[j]==0)
                    {
                    frames[j] = pages[i];
                    occurrence[j]=1;
                    j++;
                    j = j % capacity;
                    break;
                    }
                else{
                    occurrence[j] = 0;
                    j++;
                    j = j % capacity;
                }
                }
                cout.width(2);
                cout.fill('0');
                cout << pages[i] << " F    " ;
                for(int k = 0; k < capacity; k++)
                {
                cout.width(2);
                cout.fill('0');
                cout << frames[k] << " ";
                }
                cout << "\n";
                faults++;
            }
            else{
              int editedIndex = findInArrayIndex(frames,pages[i],capacity);
              occurrence[editedIndex] = 1;
              printOut(frames,pages[i],capacity);
            }
        }
    }
    return faults;
}

int FIFO(int pages[], int n, int capacity)
{
    cout << "Replacement Policy = FIFO\n";
    cout << "-------------------------------------\n";
    cout << "Page    Content of Frames\n";
    cout << "---     -----------------\n";

    int frames[capacity];
    for(int i = 0; i<capacity; i++)
    {
        frames[i] = -1;
    }
    int faults = 0, full = 0, j = 0;

    for (int i=0; i<=n; i++)
    {
        if (full < capacity)
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                frames[j] = pages[i];
                full++;
                j++;
                j = j % capacity;
                printOut(frames,pages[i],capacity);
            }
             else{
                printOut(frames,pages[i],capacity);
            }
        }
        else
        {
            if (!findInArray(frames,pages[i],capacity))
            {
                frames[j] = pages[i];
                j++;
                j = j % capacity;
                cout.width(2);
                cout.fill('0');
                cout << pages[i] << " F    " ;
                for(int k = 0; k < capacity; k++)
                {
                cout.width(2);
                cout.fill('0');
                cout << frames[k] << " ";
                }
                cout << "\n";
                faults++;
            }
            else{
              printOut(frames,pages[i],capacity);
            }
        }
    }

    return faults;
}

int main()
{
    string policy;
    int frame_number;
    int pages[4096];
    int i = 0, temp;

    cin >> frame_number;
    cout << frame_number << "\n";

    cin >> policy;
    cout << policy << endl;


    cin >> temp;
    if(temp!=-1)
    {
        pages[i] = temp;
        cout << pages[i] << "\n";
        while (pages[i] != -1){
            i++;
            cin >> pages[i];
            cout << pages[i] << "\n";
        }

    }

    if(policy == "FIFO"){
    int faults = FIFO(pages, i, frame_number);
    cout << "-------------------------------------\n";
    cout << "Number of page faults = "<< faults;
    }
    else if(policy == "CLOCK")
    {
      int faults = CLOCK(pages, i, frame_number);
      cout << "-------------------------------------\n";
      cout << "Number of page faults = "<< faults;
    }
    else if(policy == "LRU")
    {
      int faults = LRU(pages, i, frame_number);
      cout << "-------------------------------------\n";
      cout << "Number of page faults = "<< faults;
    }
    else if(policy == "OPTIMAL")
    {
      int faults = OPTIMAL(pages, i, frame_number);
      cout << "-------------------------------------\n";
      cout << "Number of page faults = "<< faults;
    }
    else cout << "Invalid replacement policy input";

    return 0;
}
