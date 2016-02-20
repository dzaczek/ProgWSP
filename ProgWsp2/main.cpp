#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <time.h>
#include <fstream>
#include <iterator>
#include <string>
#include <array>
#include <cmath>

#include <time.h> //usun ze sleepami
#include <unistd.h>

#include <sys/time.h> //for timestamp

#include <sys/stat.h>
#include <sstream>



using namespace std;

//#define NUM_THREADS     4
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define SIZE_ARRAY    256
/*
   -*
   -*
   g++ -std=c++17  zad2av2.cpp -pthread -g
   ulimit -i  120000 albo unlimited
   ulimit -s unlimited
   unlimit -v ulimited
    echo 120000 > /proc/sys/kernel/threads-max
    echo 600000 > /proc/sys/vm/max_map_count
    echo 200000 > /proc/sys/kernel/pid_max

 * -*
   -*
   -*/
typedef unsigned long long timestamp_t;

static int ilosc_przedzialow = SIZE_ARRAY;
static int size_histogram = SIZE_ARRAY;
static long long int ilosc_losowan =6000000; //100000000; //4000000; //100000000;
static int zakres_liczb = 16384;
static int rozmiar_p = zakres_liczb / ilosc_losowan;
vector<int>  vectorint;
//std::array <int,SIZE_ARRAY> histogram;
int histogram[SIZE_ARRAY];

string filename_data = "orginal.txt";
static int NUM_THREADS = 131072; //6553;
static int iloscprobek =  3;
auto NUN_sub_probek=round(log2(NUM_THREADS)+2);
time_t rawtime;
struct tm * timeinfo;
char buffer[80];


class statsy
{

public:
void set_pomiar(int numer){
        numer_pomiaru=numer;
}
void set_watki(int numer){
        ilosc_watkow=numer;
}
void set_czas(double czas){
        czas_wykonywania=czas;
}
void set_sumnik(long int incik){
        sumnik=incik;
}
long int  return_sumnik(){
        return sumnik;
}
void set_hist(const std::vector<int>& v){
        hist=v;
}
int return_watki(){
        return ilosc_watkow;
}
int return_nrpomiaru(){
        return numer_pomiaru;
}
double return_czas(){
        return czas_wykonywania;
}
int licz();
void print_hist();
int vector_size(){
        return hist.size();
}
int return_hist(int n){
        return hist[n];
}
vector<int> return_hist(){
        return hist;
}

private:
int numer_pomiaru;
int ilosc_watkow;
double czas_wykonywania;
vector<int>hist;
int hist_sum;
long int sumnik;



};



void statsy::print_hist()
{
        for (int n : hist )
                cout << n << endl;
}

int statsy::licz(){
        int sum_of_elems=0;
        for (int n : hist)
                sum_of_elems += n;
        cout <<sum_of_elems<<endl;
        return sum_of_elems;
}


static timestamp_t get_timestamp()
{
        struct timeval now;
        gettimeofday (&now, NULL);
        return now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}




struct thread_data
{ int thread_id;
  int ilosc_w; };

void *THE_FUNCTION(void *threadarg)
{
        struct thread_data *my_data;
        my_data = (struct thread_data *) threadarg;
        int PRZEDZIAL_rozmiar = ilosc_losowan / my_data->ilosc_w;
        int PRZEDZIAL_zakres_min = PRZEDZIAL_rozmiar * my_data->thread_id;
        int PRZEDZIAL_zakres_maks = PRZEDZIAL_zakres_min + PRZEDZIAL_rozmiar;
        int *wsk_array_hist;
        wsk_array_hist = histogram;
        for (long long int sek = PRZEDZIAL_zakres_min; sek < PRZEDZIAL_zakres_maks; ++sek)
        {


                long long numerprzedzialu = (vectorint[sek] * ilosc_przedzialow - 1) / zakres_liczb;
                //cout <<"\t\tID: " << my_data->thread_id<< " numerprzedzialu"  <<  numerprzedzialu<< endl;
                //cout <<"\t\tID: " << my_data->thread_id<< " sek"  <<  sek<< endl;
                //wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
                if (numerprzedzialu < ilosc_przedzialow && numerprzedzialu >= 0) {
                        wsk_array_hist[numerprzedzialu] = wsk_array_hist[numerprzedzialu] + 1;

                        // wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
                        // cout << numerprzedzialu << " " << histogram[numerprzedzialu] << " "<< w0pk <<endl;
                }
                else
                {
                        cout << "numerprzedzialu ->" << numerprzedzialu;

                }
        }
        //cout << "\t\tThread ID : " << my_data->thread_id<<endl ;
        //cout << "\t\t Message : " << my_data->ilosc_w << endl;

        //cout << "\t\t TID:"<<my_data->thread_id<<"\n\t\tPrzedzial Rozmiar" <<PRZEDZIAL_rozmiar<<"\n\t\tPrzedzial MIN: "<<PRZEDZIAL_zakres_min<<"\n\t\t Przedzial MAKS: "<<PRZEDZIAL_zakres_maks<<"\n"<<endl;
        //cout << "\t\tilosc_losowan->"<<ilosc_losowan<<endl;
        //cout << "\t\tilosc_przedzialow->"<<ilosc_przedzialow<<endl;
        //cout <<  "\t\t przyklad waetosci z zakresu" << histogram[PRZEDZIAL_zakres_min] <<endl ;
        // pthread_exit(NULL);
}

//losujemy liczbe z zakresu
int random2()
{

        return rand() % zakres_liczb + 1;
}
//load from file
void inputVint(string filename)
{
        int invar;
        ifstream inputFile;
        inputFile.open(filename);
        //inputFile >> invar;
        //  cout << invar<<endl;
        //inputFile >> invar;
        //cout << invar<<endl;
        while (inputFile >> invar) {
                vectorint.push_back(invar);
        }
        inputFile.close();
        // cout<<histogram[1]<<" "<<histogram[10]<<endl;
}

//safe to file
void outputVint(vector<int> bleblebla, string filename)
{
        ofstream outputFile;
        outputFile.open(filename);


        for (auto n : bleblebla)
                outputFile << n << '\t';

        outputFile.close();
}
bool check_if_file_exist(string filename)
{
        //return std::filesystem::exists(filename);
        //return std::experimental::filesystem::exists(filename);
        std::ifstream infile(filename);
        return infile.good();
}

void tworzHistogram()
{
        //tworzy zawsze poprawny histogram pojedynczy przebieg
        int rozmiar_p = zakres_liczb / ilosc_losowan;

        int w0pk;
        int b;

        for (auto w0pk : vectorint)
        {

                int numerprzedzialu = (w0pk * ilosc_przedzialow - 1) / zakres_liczb;
                //numerprzedzialu=numerprzedzialu;
                //cout <<numerprzedzialu <<" ";
                if (numerprzedzialu < size_histogram && numerprzedzialu >= 0) {
                        histogram[numerprzedzialu] = histogram[numerprzedzialu] + 1;
                        // cout << numerprzedzialu << " " << histogram[numerprzedzialu] << " "<< w0pk <<endl;
                }
                else
                {
                        cout << "numerprzedzialu ->" << numerprzedzialu;
                }

        }


}


int createSumArray(int* arr, int size)
{
        int wynik = 0;
        for (int i = 0; i < size; i++)
                wynik += arr[i];

        return wynik;
}

double diffclock( clock_t clock2, clock_t clock1 ) {

        double diffticks = clock1 - clock2;
        double diffms    = diffticks / ( CLOCKS_PER_SEC / 1 );

        return diffms;
}


void array_histogra_to_file(string filename)
{
        //int arr*=histogram;
        ofstream myfile(filename);
        if (myfile.is_open())
        {
                for (int i = 0; i < size_histogram; ++i) { myfile << i + 1 << "\t" << histogram[i] << "\n"; }
        }
//  cout <<"Zapisano plik wynikowy historamu o nazwie: "<<filename<<endl;
}

void string_to_file(string filename, string data)
{
        //int arr*=histogram;
        ofstream myfile(filename, std::ios::app);
        if (myfile.is_open())
        {
                myfile << data;
        }
        else
        {
                cout << "***FUCK" << endl;
        }
//  cout <<"Zapisano plik wynikowy historamu o nazwie: "<<filename<<endl;
}
//insert data to table
void data_generate()
{
        for (long long int i = 0; i < ilosc_losowan; i++)
        {
                vectorint.push_back(random2());
        }
        cout << "\t Wygenerowano tablice o rozmarze: "  << ilosc_losowan << endl;
}
void gnuplotoutput(string filename,string kapibara)
{
        string ploter="reset \n \
set term png truecolor \n \
set datafile separator ' ' \n\
set term png size 2900, 1000\n \
set output \""+filename+"profit_line.png\" \n \
set xlabel \"ZAKRES\" \n \
set ylabel \"WARTOSCI\" \n \
set grid \n \
set boxwidth 1 relative \n \
set key below \n \
set key font \",20\" \n \
set style fill transparent solid 1 \n \
set key autotitle columnhead \n \
set key samplen 2 spacing 1 \n \
plot [0:256] for [col=2:"+kapibara+"] '"+filename+"STATS.csv'   using 1:(column(int(col))) w lines  title columnhead(col)\n \
reset \n\
set term png truecolor \n \
set datafile separator ' ' \n \
set term png size 2900, 1000 \n \
set output \""+filename+"profit_pointers.png\" \n \
set xlabel \"ZAKRES\" \n \
set ylabel \"WARTOSCI \" \n \
set grid \n \
set boxwidth 1 relative \n \
set key below \n \
set key font \",20\" \n \
set style fill transparent solid 1 \n \
set key autotitle columnhead \n \
set key samplen 2 spacing 1 \n \
set pointsize 4 \n \
plot [0:256] for [col=2:"+kapibara+"] '"+filename+"STATS.csv'   using 1:(column(int(col))) w  points  title columnhead(col)\n\
";


        string_to_file(filename+"stat.gp", ploter);



}
void gnuplotoutput(string filename,string kapibara,string source)
{
        string ploter="reset \n \
set term png truecolor \n \
set datafile separator ' ' \n\
set term png size 2900, 1000\n \
set output \""+filename+""+source+"profit_line.png\" \n \
set xlabel \"ZAKRES\" \n \
set ylabel \"WARTOSCI\" \n \
set grid \n \
set boxwidth 1 relative \n \
set key below \n \
set key font \",20\" \n \
set style fill transparent solid 1 \n \
set key autotitle columnhead \n \
set key samplen 2 spacing 1 \n \
plot [0:256] for [col=2:"+kapibara+"] '"+filename+""+source+"'   using 1:(column(int(col))) w lines  title columnhead(col)\n \
reset \n\
set term png truecolor \n \
set datafile separator ' ' \n \
set term png size 2900, 1000 \n \
set output \""+filename+""+source+"profit_pointers.png\" \n \
set xlabel \"ZAKRES\" \n \
set ylabel \"WARTOSCI \" \n \
set grid \n \
set boxwidth 1 relative \n \
set key below \n \
set key font \",20\" \n \
set style fill transparent solid 1 \n \
set key autotitle columnhead \n \
set key samplen 2 spacing 1 \n \
set pointsize 4 \n \
plot [0:256] for [col=2:"+kapibara+"] '"+filename+""+source+"'   using 1:(column(int(col))) w  points  title columnhead(col)\n\
";


        string_to_file(filename+source+".gp", ploter);
        string filestat="gnuplot "+filename+source+".gp";
        system((filestat).c_str()); //na samym koncu duzo danych dla gnuplota


}
void anychart(string filename,string num_column,string typegraph)
{
//         string ploter="reset \n \
// set term png truecolor \n \
// set datafile separator ' ' \n \
// set term png size 800, 600 \n \
// set output  \n \
// set ylabel \"czas [ms]  \" \n \
// set grid \n \
// set boxwidth 1 relative \n \
// set nokey  \n \
// set key font \",6\" \n \
// set style fill transparent solid 1 \n \
// set boxwidth 0.5 \n \
// set style fill solid 1.000000 border -1 \n \
// set bmargin 3 \n \
// set key autotitle columnhead \n \
// plot '"+filename+"'    using 0:"+num_column+":xtic(1) w "+typegraph+" title columnhead,    ''          using 0:2:2 with labels  rotate by -90  font   'arial,14' tc lt 5 notitle";
string ploter="reset\n \
 set term png truecolor\n \
 set datafile separator ' '\n \
 set term png size 900,800 \n \
 set output \""+filename+"_"+typegraph+".png\" \n \
 set ylabel \"czas [ms]  \" \n \
set xlabel \"Liczba wątków\" \n \
 set grid \n \
 set xtics rotate \n \
 set nokey \n \
 set key font \",14\" \n \
 set style fill transparent solid 1 \n \
 set boxwidth 0.5 \n \
 set style fill solid 1.000000 border -1 \n \
 set bmargin 3 \n \
set ytics auto \n \
 set y2range [:100] \n \
 set y2tics auto \n \
 #set y2tics nomirror \n \
 set ytics nomirror \n \
 set y2label \"% poprawnosci\" \n \
 set key autotitle columnhead \n \
 set bmargin 6 \n \
set tmargin 3 \n \
 plot '"+filename+"' using 0:2:xtic(1) axes x1y1 w boxes t columnhead,  \\\n\
	''       using 0:2:2 with labels  rotate by -90 offset -0,+1  font   'arial,8'   notitle, \\\n\
	''	 using 0:3 axes x1y2  w lines t columnhead lt 2 lc rgb \"red\" lw 3 \n";



        string_to_file(filename+".gp", ploter);
        string filestat="gnuplot "+filename+".gp";
        system((filestat).c_str()); //na samym koncu duzo danych dla gnuplota


}




void histograms_to_file(string str77,vector<statsy>& statystyki){
        for (int ipk=0; ipk<ilosc_przedzialow; ipk++)  {

                vector<int> column;
                ostringstream headers1;

                if (ipk==0) {
                        headers1<<"N ";
                        for(statsy header : statystyki)
                        {
                                headers1 <<"H:"<<header.return_watki()<<"-P:"<<header.return_nrpomiaru()<<" ";

                                //string_to_file(str77 + "/STATS.csv", headers1.str());
                        }
                        headers1 <<endl;

                }

                headers1 <<ipk+1<<" ";
                for (statsy mrs : statystyki )
                {
                        //cout <<mrs.return_watki()<<" "<<mrs.return_nrpomiaru()<<" "<<mrs.licz()<<" Size:"<< mrs.vector_size()<<endl;
                        //for (int iks : )

                        // vector<int>row;
                        headers1 << mrs.return_hist(ipk)<<" ";

                }
                //cout <<endl;
                headers1 <<"\n";
                //cout << headers1.str();
                string_to_file(str77+"STATS.csv",headers1.str());
        }

}

// void print_array(int n,int m,int arr[][n]){
//     int i, j;
//     for (i = 0; i < m; i++)
//     {
//         for (j = 0; j < n; j++)
//         {
//             (i==m-1)?(cout << arr[i][j]<<endl):(cout << arr[i][j]<<" ")
//
//         }
//     }
// }


void print_ele_of_vector(vector<int>& dane){
        for (int mrd : dane) {
                cout <<mrd<<endl;
        }
}

void average_histogram(string str77,vector<statsy>& statystyki,int NUM_THREADS_S, int num_sub,string fname){
        vector<int> typki; while(NUM_THREADS_S >=1) {typki.push_back(NUM_THREADS_S); (NUM_THREADS_S <= 4) ? NUM_THREADS_S = NUM_THREADS_S - 1 : NUM_THREADS_S = NUM_THREADS_S / 2; }
        int num_of_typki=typki.size();
//        print_ele_of_vector(typki);
        cout <<num_of_typki<<endl;
        cout<<num_sub<<endl; //ilosc watkow
        cout <<SIZE_ARRAY<<endl;
        //std::vector<vector <long int>> xdimV;
        long int xdimV[num_of_typki][SIZE_ARRAY]={0};
        long double timeV[num_of_typki]={0.000000};
        long int bladV[num_of_typki]={0};
        int semafor=0;
        for(statsy core : statystyki)
        {        //cout<<core.hist.size();

                //    cout <<"test1"<<endl;//
                for(int pomiarki=0; pomiarki<num_of_typki; pomiarki++) {
                        //    cout <<"        "<<typki[pomiarki]<<endl;
                        if(core.return_watki()==typki[pomiarki]) {
                                semafor+=1;
                                //    cout<< "thr: "<<core.return_watki()<<" time: " <<core.return_czas()<<endl;
                                timeV[pomiarki]+=core.return_czas();
                                bladV[pomiarki]+=core.return_sumnik();
                                //    cout <<"test3"<<endl;
                                for(int ipen=0; ipen<size_histogram; ipen++)
                                {
                                        //        cout <<"test4"<<endl;
                                        xdimV[pomiarki][ipen]+=core.return_hist(ipen);
                                        //        cout<< " " << core.return_watki() <<" "<<core.return_hist(ipen)<< " ";
                                        //if(ipen==255){xdimV[pomiarki][ipen]=xdimV[pomiarki][ipen]/iloscprobek;cout<<"****done";}
                                        //if(semafor==iloscprobek-1){xdimV[pomiarki][ipen]=xdimV[pomiarki][ipen]/iloscprobek;cout<<"****done";semafor=0;}
                                }
                                // if(pomiarki==num_of_typki-1){timeV[pomiarki]=timeV[pomiarki]/iloscprobek;}
                        }

                }
        }
        //cout <<str77<<endl;
        //cout<<endl;

        for (int ja = 0; ja < size_histogram; ++ja) {
                for (int ia = 0; ia < num_of_typki; ++ia)
                {
                        xdimV[ia][ja]=xdimV[ia][ja]/iloscprobek;
                }
        }


        std::ostringstream masteroftime;
        masteroftime<<"Wątki Czas&{1}Pracy '%&{1}Porawność'"<<endl;
        for (int ia = 0; ia < num_of_typki; ia++)
        {

                //    timeV[ia]=timeV[ia]/iloscprobek;
                //cout <<typki[ia]<<": "<<timeV[ia]/iloscprobek<<" "<<endl;
                long int avg=bladV[ia]/iloscprobek;
                //avg=avg*100;
                //cout << avg/iloscprobek <<" "<< (float)avg/(float)iloscprobek<<endl;
                double avg1= (avg/(double)ilosc_losowan)*100.0;
                masteroftime<<typki[ia]<<' '<<timeV[ia]/iloscprobek<<' '<< std::fixed<<avg1<<'\n';

        }
            cout << masteroftime.str();
        string_to_file(str77+"AVERAGE_TIME.csv",masteroftime.str());
        anychart(str77+"AVERAGE_TIME.csv", "2", "boxes");

        for (int j = 0; j < size_histogram; ++j)
        {
                std::ostringstream danke;
                if(j==0) {

                        danke <<"N ";

                        for(int bxc : typki) {
                                danke <<bxc<<" ";
                        }
                        danke<<endl;
                }
                danke<<j+1<<" ";
                for (int i = 0; i < num_of_typki; ++i)
                {
                        danke << xdimV[i][j] << ' ';
                }
                danke <<endl;
                string_to_file(str77+fname,danke.str());
        }

        gnuplotoutput(str77,to_string(num_of_typki+1),fname);

}

bool divider(int rotator){
        bool x;

        if ( iloscprobek<4 ||  (iloscprobek/4)==rotator || (iloscprobek/2)==rotator || rotator==1 || rotator==iloscprobek )
        {
                x=true;
        }
        else{
                x=false;
        }
        return x;
}

int main ()
{


        //cout << "**** max_size: " << vectorint.max_size() << "\n";
        cout << "*** PID: " << getpid() << endl;
        //sleep (3);
        pthread_t threads[NUM_THREADS];
        struct thread_data td[NUM_THREADS];
        srand(time(NULL));
        int rc;
        int i;
        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y-%m-%d_%I:%M:%S", timeinfo);
        std::string str77(buffer);
        vector <statsy> statystyki;
        statsy *s1;


        //generujemy vector losowych danych z zakresu
        if (!check_if_file_exist(filename_data)) {
                data_generate();
                outputVint(vectorint, filename_data);
        }
        else
        {
                inputVint(filename_data);
                cout << "plik istnial zaladowano dane z pliku: " << filename_data << endl;
                // cout <<vectorint[1]<<vectorint[10]<<vectorint[15]<<endl;
        }

        //tworzymy histogram
        tworzHistogram();


        array_histogra_to_file("wzor.txt");

        //for (int i = 0; i < size_histogram; i++) {
        //      cout<< i<<"->"<<histogram[i]<<endl;
        //}
        //czyscimy tablice
//////LOOP/////LOOP/////LOOP/////LOOP/////LOOP/////LOOP/////LOOP/////LOOP///
        for (int rotator = 1; rotator <= iloscprobek; rotator++) {


                string str76 = str77 + "_" + to_string(rotator);
                int NUM_THREADS_S=NUM_THREADS;

                char str75[21];
                // size_t length = str76.copy(str75, str76.length());
                //cout << "length" << length << endl;
                // str75[length] = "\0";

                const int dir_err = mkdir(str76.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (-1 == dir_err)
                {
                        printf("Error creating directory!n");
                        exit(1);
                }




                for (int i = 0; i < size_histogram; i++) {
                        histogram[i] = '\0';


                }
                string head = "|THREADS|CORE TIME|Timestamp| Chrono | Ele Hist| TIME/CORE |NUM/THREADS|";
                string head1 = ";THREADS;CORE TIME;Timestamp; Chrono ; Ele Hist; TIME/CORE ;NUM/THREADS;\n";
                if( divider(rotator)) {
                        cout << "-----------------------------------------------------------------------" << endl;
                        cout << head << endl;
                        cout << "-----------------------------------------------------------------------" << endl;
                }
                string_to_file(str76 + "/STATS.csv", head1);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                while (NUM_THREADS_S >= 1)
                {
                        //  cout<<"\t\t\t ***START THR***"<<" \tNR: "<<NUM_THREADS <<endl;
                        clock_t begin = clock();
                        timestamp_t t0 = get_timestamp();
                        auto start = std::chrono::steady_clock::now();
                        for ( i = 0; i < NUM_THREADS_S; i++ ) {
                                //cout <<"main() : creating thread, " << i << endl;
                                td[i].thread_id = i;
                                td[i].ilosc_w = NUM_THREADS_S;

                                rc = pthread_create(&threads[i], NULL, THE_FUNCTION, (void *)&td[i]);
                                if (rc) {
                                        cout << "Error:unable to create thread," << rc << endl;
                                        exit(-1);

                                }
                                // pthread_detach(threads[i]);
                        }
                        for (i = 0; i < NUM_THREADS_S; i++) pthread_join(threads[i], NULL);
                        // cout <<"test" <<pthread_exit(NULL)<<endl;
                        timestamp_t t1 = get_timestamp();
                        clock_t end = clock();
                        auto stop = std::chrono::steady_clock::now();

//for(i=0; i<NUM_THREADS_S; i++)
                        //  {
                        //         status*   status;
                        //        pthread_join(threads[i], &status);
                        //}

                        double elapsed_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
                        string s = to_string(NUM_THREADS_S);
                        double secs = (t1 - t0) / 1000000.0L;
                        double diffcores = diffclock(begin, end);
                        double diffcore = diffcores / NUM_THREADS_S;
                        int iloscnawatek = ilosc_losowan / NUM_THREADS_S;
                        long int sumnik=createSumArray(histogram, SIZE_ARRAY);

                        //cout<< "|"<<NUM_THREADS <<"|"<<diffclock(begin,end)<<"|"<< secs<<"|"<<elapsed_seconds<<"|"<< createSumArray(histogram,SIZE_ARRAY) <<"|"<<endl;

                        if(divider(rotator)) {
                                printf("|%7d|%9f|%9f|%s%5f%s|%s%9d%s|%11f|%s%11u%s|\n", NUM_THREADS_S, diffcores, secs, KGRN, elapsed_seconds / 1000000000, KNRM, KBLU, sumnik, KNRM, diffcore, KBLU, iloscnawatek, KNRM);
                                cout << "-----------------------------------------------------------------------" << endl;
                        }
                        std::ostringstream mydane;

                        mydane << ";" << NUM_THREADS_S << ";" << diffcores << ";" << secs << ";" << elapsed_seconds / 1000000000 << ";" << sumnik<< ";" << diffcore << ";" << iloscnawatek << ";\n";

                        s1=new statsy;
                        s1->set_pomiar(rotator);
                        s1->set_watki(NUM_THREADS_S);
                        s1->set_sumnik(sumnik);
                        s1->set_czas(elapsed_seconds/1000000000);
                        vector<int>vhist;
                        auto it = vhist.begin();
                        vhist.insert(it,histogram,histogram+256);
                        s1->set_hist(vhist);
                        statystyki.push_back(*s1);
                        string_to_file(str76 + "/STATS.csv", mydane.str());
//   cout<<"\t\t\t ***END THR***"<<endl;
                        array_histogra_to_file(str76 + "/" + s + "watek.txt");

                        const int pki = (NUM_THREADS_S <= 4) ? NUM_THREADS_S = NUM_THREADS_S - 1 : NUM_THREADS_S = NUM_THREADS_S / 2;

                        for (int i = 0; i < size_histogram; i++) {
                                histogram[i] = '\0';
                        }


                }

        }


        //for (int i = 0; i < size_histogram; i++) {
        //    cout<< i<<"->"<<histogram[i]<<endl;
        //}
        //cout<<"\t\t\t ***SAFE TO FILE***"<<endl;

        // cout <<isprint(timestart)<<endl;

        cout << "\t\t\t ***END***" << endl;
/*

   Globalne Statystyki

 */

        histograms_to_file(str77,statystyki);
        gnuplotoutput(str77,to_string(iloscprobek*NUN_sub_probek+1));

        average_histogram(str77,statystyki,NUM_THREADS,NUN_sub_probek,"average.csv");
        //    string filestat="gnuplot "+str77+"stat.gp";
        //    system((filestat).c_str()); //na samym koncu duzo danych dla gnuplota

        //auto gooo="cd "+str77+"/";
        //system("cd str77");
        // char cmd=;
        //system("gnuplot;reset;set term png truecolor;set term png size 1600, 400;set output 'profit_dots.png';set xlabel 'ZAKRES';set ylabel 'WARTOSCI';set grid;set boxwidth 1.95 relative;set style fill transparent solid 0.5 noborder;list=system('ls -1B *watek.txt | sort -h');plot for[file in list] file  using 1:2 w points  title  file; exit;");
        return 0;
}

/*
   Należy zbudować aplikację obliczającą histogram tablicy bajtów o podanej specyfikacji:
   1. Aplikacja działa sekwencyjnie lub tworzy 2,4,8,10,12,14,16 wątków.
   2. Rozmiar tablicy musi być nie mniejszy niż 4 mln bajtów.
   3. Tablica danych wejściowych do wszystkich prób powinna być identyczna, czyli musi
   4. być zapisywana w pliku.
   5. Elementy są zliczane bezpośrednio do wspólnej tabeli histogramu o wymiarach 256
   6. pól typu integer.
   7. Należy dokonać pomiarów uśrednionego czasu obliczenia histogramu dla każdej
   8. opcji programu.
   9. Należy porównać czy wyniki są za każdym razem identyczne.
   10. Dane wyjściowe (histogram) powinny być za każdym razem zapisywane w
   oddzielnym pliku.

 */
