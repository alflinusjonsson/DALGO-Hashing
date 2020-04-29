#include "ragnarstest.h"


#include "studentsHashtableforstrings.h"

#include <string>
#include <vector>
#include <set>
#include <QElapsedTimer>

#include <iostream>
#include <QDebug>
#include <assert.h>

#include <stdio.h>

using namespace std;

bool okToInsert(HashtableForStrings& tab, const string& str){
    int size1 = tab.size();
    string value = str + string(" -value");
    tab.insert(str, value);
    int size2 = tab.size();
    bool okSize = (size2-size1)==1;
    bool okValue = tab.valueFromKey(str)==value;

    return okSize && okValue;
}

bool okToRemove(HashtableForStrings& tab, const string& str){

    int size2 = tab.size();
    tab.remove(str);
    int size1 = tab.size();
    bool okSize = (size2-size1)==1;


    return okSize;
}



/************************************************
ANROP:   int eclapsed = timeTest();
VERSION: 110225 nora
UPPGIFT: Poppulerar hashtabellen med mÂnga str‰ngar
         och m‰ter tiden. Antal millisekunder returneras.
*************************************************/
int  timeTest( )
{
    cerr << "startar timeTest." << endl;
    HashtableForStrings tab(47017);

    QElapsedTimer timer;
    timer.start();
    for (int i=0;i<25000;++i){
        char str[100];

        sprintf(str, "hello%d", i);
        string s = str;

        tab.insert(s);
        tab.contains("dummy");
    }

    int elapsed = (int) timer.elapsed();
    return elapsed;

} //timeTest



// Vi skaper en kort (11 rader) hashtabell och insertar 5 slumpsträngar
// Detta upprepas måga gÂnger. Syftet är att testa att studentens kod
// stegar "runt hurnet".
bool extraTest2(){
    cerr << "startar extraTest2." << endl;

    for (int ite = 0; ite < 10000; ++ite){
        HashtableForStrings tab(11);
        vector<string> vecStr;

        for (int n = 0; n < 5; ++n){
            char str[100];
            sprintf(str, "ite%d__n%d__slump%d", ite, n, rand());
            string s = str;


            vecStr.push_back(s);

            bool ok = okToInsert((tab), s);


            if (!ok){
                qDebug() << "Failed to insert: " << s.c_str() << endl;
                return false;
            }
        }
        for (string s : vecStr){
            if (!tab.contains(s)){
                qDebug() << "table does not contain: " << s.c_str() << endl;
                return false;
            }
        }
    }

    qDebug() << "extraTest2 lyckades";

    return true;

}
// extratest: Vi skapar en kort (11 rader) hashtabell och gör väldigt
// många insert och remove till denna. Vi jämför med std::set.
bool extraTest(){

    qDebug() << "startar extraTest." << endl;

    HashtableForStrings tab(11);

    set<string> theSet;


    for (int i=0;i<10000;++i){
        char str[100];
        sprintf(str, "random %d", rand()%25);
        string s = str;

        if (theSet.find(s) != theSet.end()){// Strängen s skall finnas
            bool ok1 = tab.contains(s);
            bool ok2 = okToRemove((tab), s);
            theSet.erase(s);
            if (!ok1 || !ok2){
                cout << "FEL 1 i extratest!" << endl;
                return false;
            }
        }
        else { // strängen s skall ej finnas
            bool ok = !tab.contains(s);
            if (!ok){
                cout << "FEL 2 i extratest!" << endl;
                return false;
            }
            if (theSet.size()<5) { // Stoppa in strängen
                theSet.insert(s);
                bool ok = okToInsert((tab), s);

                if (!ok){
                   cout << "FEL 3 i extratest!" << endl;
                   return false;
               }
            }
        }
    }

    qDebug() << "extraTest lyckades";

    return true;
}

/************************************************
ANROP:   bool ok= hashTest(testAlsoRemove);
VERSION: 110309 nora
UPPGIFT: Verifierar att logiken tycks st‰mma.

         om testAlsoRemove==true testas ‰ven
         removefunktionen

*************************************************/
bool hashTest(bool testAlsoRemove )
{
    qDebug() << "startar hashTest";


    const int N = 23000;
    HashtableForStrings tab(47017); // Minst 2*N

    bool ok = true;

    qDebug() << "Försöker stoppa in " << N << " unika strängar...";

    for (int i=0; ok && i<N;++i){
        char str[100];
        sprintf(str, "Hash%dTest", i);
        string s = str;
        ok = ok &&  okToInsert((tab), s);
        if (!ok)
            qDebug() << "hashTest 1: Insert(" << s.c_str() <<") returnerade ej true" << endl;
    }

    assert( ok );
    qDebug() << "Verifierar att tabellen nu contains dessa strängar...";

    for (int i=0; ok && i<N;++i){
        char str[100];
        sprintf(str, "Hash%dTest", i);
        string s = str;
        ok = ok && tab.contains(s);
        if (!ok)
            qDebug() << "hashTest 3: contains(" << s.c_str() <<") returnerade ej true" << endl;
    }

    assert( ok );
    qDebug() << "Verifierar att tabellen inte innehåller andra strängar...";

    for (int i=0; ok && i<N;++i){
        char str[100];
        sprintf(str, "DUM%dTest", i);
        string s = str;
        ok = ok && !tab.contains(s);
        if (!ok)
            qDebug() << "hashTest 4: contains(" << s.c_str() <<") returnerade  true" << endl;
    }

    assert( ok );


    if (testAlsoRemove){
        qDebug() << "Tar bort de " << N << " strängarna...";

        for (int i=0; ok && i<N;++i){
            char str[100];
            sprintf(str, "Hash%dTest", i);
            string s = str;
            ok = ok &&  okToRemove((tab), s);
            if (!ok)
                qDebug() << "hashTest 5: remove(" << s.c_str() <<") returnerade ej true" << endl;
        }
        assert( ok );
        qDebug() << "Stoppar in samma " << N << " strängar igen..";

        for (int i=0; ok && i<N;++i){
            char str[100];
            sprintf(str, "Hash%dTest", i);
            string s = str;

            ok = ok && okToInsert((tab), s);
            if (!ok)
                qDebug() << "hashTest 6: insert(" << s.c_str() <<") returnerade ej true" << endl;
        }
        assert(ok);
    }


    if (testAlsoRemove)
        ok = ok && extraTest();

    ok = ok && extraTest2();
    return ok;
} // hashTest


//***********************************************************************
// ANROP:   ok = ragnarsTest( );
// VERSION: 2011-03-09
// UPPFIFT: Testar en eller flera rutiner som studenten har skrivit.
//
//***********************************************************************
bool ragnarsTest(){

    cout << "\n\n-----------------------------------------------------\n";
    cout << "ragnarsTest testar kod av " << nameOfStudent() << "\n\n";


    if ( std::string( "Homer Simpson" ) == nameOfStudent() ) {
        cout << "\n\nFelaktigt namn!\7\n";
        assert( false );
    }

    const bool testAlsoRemove = true;

    bool ok = hashTest( testAlsoRemove );

    if (ok){
        int eclapsed = timeTest();
        cout << "timeTest() returnerade " << eclapsed <<" ms" << endl;
        if (eclapsed<200)
            cout << "vilket ‰r ok" << endl;
        else {
            cout << "vilket ‰r mycket!\7" << endl;

#ifdef DEBUG
            cout << "prova release mode!\7" << endl;
#endif

        }
        ok = ok && eclapsed < 1000;
    }



    cout << (ok ? "ragnarsTestLyckades" : "ragnarsTest MISSLYCKADES\7") << endl;
    return ok;
}


