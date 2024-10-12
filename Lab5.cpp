#include <iostream>
#include <stdexcept>
#include <map>
#include <fstream>
#include <string>

class SBase{
    public:
    virtual int Get()=0;
};

class SFile:public SBase{
    std::ifstream file;
    public:
    SFile(std::string fileName){
        file.open(fileName);
        if(!file.is_open()){
            throw std::runtime_error("can't open file");
        }
    }
    ~SFile(){
        file.close();
    }
    int Get(){
        int buffer;
        if(file>>buffer){
            return buffer;
        } else {
            return -1;
        }
    }
};
class SKeyboard:public SBase{
    public:
    int Get(){
        int buffer;
        if(std::cin>>buffer){
            return buffer;
        } else {
            return -1;
        }
    }
};
class SQueue:public SBase{
    int* arr;
    int len;
    int index;
    public:
    SQueue(int *ptr,int size): arr(ptr),len(size),index(0){};
    int Get(){
        if(index<len){
            return arr[this->index++];
        } else {
            return -1;
        }
    }
};

class Freq{
    protected:
    std::map<int,int> frequency;
    public:
    virtual void calc(SBase& numberSource){
        int buffer=0;
        buffer=numberSource.Get();
        while(buffer>=0){
            this->frequency[buffer]++;
            buffer=numberSource.Get();
        }
    }
    friend std::ostream& operator<<(std::ostream& os,const Freq& freq){
        for(std::map<int,int>::const_iterator iter=freq.frequency.begin();iter!=freq.frequency.end();iter++){
            os << "\nnumber = " << iter->first << " amount of it = " << iter->second;
        }
        os << "\n";
        return os;
    }
};

class Diap:public Freq{
    protected:
    int amount;
    int max;
    int min;
    public:
    void calc(SBase& numberSource){
        int buffer=0;
        buffer=numberSource.Get();
        this->max = buffer;
        this->min = buffer;
        this->amount = 1;
        while(buffer>=0){
            this->frequency[buffer]++;
            this->amount++;
            if(this->max<buffer){
                this->max = buffer;
            }
            if(this->min>buffer){
                this->min = buffer;
            }
            buffer=numberSource.Get();
        }
    }
    friend std::ostream& operator<<(std::ostream& os,const Diap& diap){
        for(std::map<int,int>::const_iterator iter=diap.frequency.begin();iter!=diap.frequency.end();iter++){
            os << "\nnumber = " << iter->first << " amount of it = " << iter->second;
        }
        os << "\ntotal amount of numbers = " << diap.amount;
        os << "\nmin number = " << diap.min;
        os << "\nmax number = " << diap.max << "\n";
        return os;
    }
};

void randomIntArrFill(int* arr,int n,int A=1,int B=100){
    srand(time(0));
    for(int i=0;i<n;i++){
        arr[i] = A+(rand())%(B-A+1);
    }
}

int main(){
    SKeyboard keyboardReadTest;
    for(int i=0;i<5;i++){
        std::cout << keyboardReadTest.Get() << "\t";
    }
    std::cout << "\n";

    std::string fileName="file_for_test.txt";
    SFile fileReadTest(fileName);
    for(int i=0;i<10;i++){
        std::cout << fileReadTest.Get() << "\t";
    }
    std::cout << "\n";

    int n = 8,*m = new int[n];
    randomIntArrFill(m,n);
    SQueue queueReadTest(m,n);
    for(int i=0;i<10;i++){
        std::cout << queueReadTest.Get() << "\t";
    }
    std::cout << "\n\n";
    
    SFile fileToFreqTest(fileName);
    Freq freqTest;
    freqTest.calc(fileToFreqTest);
    std::cout << "frequency from file = " << freqTest << "\n";

    int k = 200,*arr = new int[k];
    randomIntArrFill(arr,k);
    SQueue queueToDiapTest(arr,k);
    Diap diapTest;
    diapTest.calc(queueToDiapTest);
    std::cout << "diapason from queue = " << diapTest;
    delete[] m;
    return 0;
}