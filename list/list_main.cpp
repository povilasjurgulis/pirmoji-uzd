#include "list_deklaracijos.h"

//Su vektoriais: pradzia!
int main(){
    cout<<"Spauskite 1, jeigu norite pradeti darba, 2 - jeigu norite baigti darba: "; 
    cin>>p.e; ivedimas1(p.e, "pradeti", "baigti", 1, 1, 2);
    if(p.e == 2) return 0;
    time_point<high_resolution_clock> start; // Sukuriame laiko pradzios kintamaji

    srand(time(NULL));
    cout<<"Spauskite 1, jeigu norite, kad galutiniam balui butu naudojamas vidurkis, 2 - jeigu mediana: "; 
    cin>>p.pasirinkimas; ivedimas1(p.pasirinkimas, "vidurki", "mediana", 1, 1, 2);
    cout<<"Spauskite 1, jeigu norite sugeneruoti atsitiktinius failus ir juos naudoti rezultatams, 2 - jeigu norite kitu pasirinkimu: "; 
    cin>>p.ar_generuoti_failus; ivedimas1(p.ar_generuoti_failus, "sugeneruoti", "kiti pasirinkimai", 1, 1, 2);
    if(p.ar_generuoti_failus==1)
    { 
        //cout<<"Iveskite, kiek studentu norite sugeneruoti: spauskite 1, jeigu 1000 studentu, 2 - jeigu 10 tukstanciu, 3 - jeigu 100 tukstanciu, 4 - jeigu 1 milijona, 5 - jeigu 10 milijonu: ";
        cin>>p.stud_kiekis; ivedimas1(p.stud_kiekis, "", "", 0, 1, 5);
        if(p.stud_kiekis==1) p.stud_kiekis=1000;
        else if(p.stud_kiekis==2) p.stud_kiekis=10000;
        else if(p.stud_kiekis==3) p.stud_kiekis=100000;
        else if(p.stud_kiekis==4) p.stud_kiekis=1000000;
        else if(p.stud_kiekis==5) p.stud_kiekis=10000000;
        file_generavimas(p.stud_kiekis);
        p.choice=4;
    }
    else{
    cout<<"Spauskite 1, jeigu norite viska rasyti ranka. 2 - jeigu norite, kad tik pazymiai butu atsitiktinai sugeneruoti. \n3 - jeigu norite, kad pazymiai, studentu vardai ir pavardes butu atsitiktinai sugeneruoti. ";
    cout<<"Spauskite 4, jeigu norite, kad visi duomenys butu nuskaityti is failo: "; 
    cin>>p.choice; ivedimas2(p.choice);
    }
    //If statement'ai, kurie atlieka veiksmus pagal vartotojo pasirinkima:
    ifs(vard_size, pav_size, p, st, studentai, vardai, pavardes, randomVyrVardai, randomMotVardai, randomVyrPavarde, randomMotPavarde, start);

    vardai.clear();
    pavardes.clear();
    auto end = std::chrono::high_resolution_clock::now(); // Skaiciavimo pabaiga
    std::chrono::duration<double> diff = end-start; // Skaiciuojame skirtuma

    int rikiavimas;
    cout << "Pasirinkite, pagal ka rikiuoti:\n" << "  1 - pagal varda"<< "  2 - pagal pavarde"<< "  3 - pagal galutini bala: "; 
    cin >> rikiavimas;
    ivedimas3(rikiavimas);
    auto start1 = std::chrono::high_resolution_clock::now(); // Pradedame skaiciuoti laika

    //Rikiavimas:
    rikiavimasFun(studentai, rikiavimas);

    auto end1 = high_resolution_clock::now(); // Skaiciavimo pabaiga
    duration<double> diff1 = end1-start1; // Skaiciuojame skirtuma
    cout<<studentai.size()<<" studentu rikiavimas didejimo tvarka uztruko: "<<fixed<<setprecision(4)<<diff1.count()<<" s"<<endl;

    int dydis = studentai.size();
    cout<<"Ar norite, kad rezultatai butu isvedami i du atskirus failus? 1 - i du atskirus failus, 2 - i ekrana, 3 - niekur neisvesti: ";
    cin>>p.kur_isvesti; ivedimas1(p.kur_isvesti, "isvesti i failus", "neisvesti i failus", 0, 1, 3);
    string pav = " "; // Failo pavadinimas

    auto start2 = high_resolution_clock::now(); // Pradedame skaiciuoti laika

    cout<<"Spauskite 1, jeigu norite, kad studentu konteineris butu isskaidytas i du naujus to paties tipo konteinerius: kietiakai ir nuskriaustukai, "<<endl; 
    cout<<"2 - jeigu norite isskaidyti panaudojant tik viena nauja konteineri nuskriaustukai, "<< endl;
    cout<<"3 - jeigu norite naudoti 3 strategija: ";
    cin>>p.koks_konteineris; ivedimas1(p.koks_konteineris, "du naujus konteinerius", "viena nauja konteineri", 0, 1, 3);

    //Studentu padalinimas i dvi grupes:
    Timer t2;
    if(p.koks_konteineris == 1)
    for(auto& studentas : studentai)
    {
        if(studentas.galutinis>=5)
            kietiakai.push_back(studentas);
        else
            nuskriaustukai.push_back(studentas);
    }
    else if (p.koks_konteineris == 2)
    {
    for (auto it = studentai.begin(); it != studentai.end(); )
    {
        if (it->galutinis < 5) 
        {
            // Add to nuskriaustukai
            nuskriaustukai.push_back(*it);
            // Erase the current element and update the iterator
            it = studentai.erase(it);
        } 
        else 
        {
            // Increment the iterator when we don't remove an element
            ++it;
        }
    }
    }
    else if(p.koks_konteineris == 3)
    {
    // Vietoj ciklo galima panaudoti std::partition arba std::remove_copy_if
    std::copy_if(studentai.begin(), studentai.end(), 
                 std::back_inserter(kietiakai), 
                 [](const Studentas& s) { return s.galutinis >= 5.0; });
                 
    std::copy_if(studentai.begin(), studentai.end(), 
                 std::back_inserter(nuskriaustukai), 
                 [](const Studentas& s) { return s.galutinis < 5.0; });
    
    // Arba alternatyviai, vienas kopijavimas ir vienas transform:
    std::partition_copy(studentai.begin(), studentai.end(),
                       std::back_inserter(kietiakai),
                       std::back_inserter(nuskriaustukai),
                       [](const Studentas& s) { return s.galutinis >= 5.0; });
    }
    
    cout<<dydis<<" Studentu skirstymas i dvi grupes/kategorijas uztruko: "<<fixed<<setprecision(4)<<t2.elapsed()<<" s"<<endl;
    if(p.kur_isvesti==3) return 0;

    //Rezultatu isvedimas:
    if(p.kur_isvesti==2)
    isvedimasFun(p, studentai, pav, vard_size, pav_size);
    Timer t3;
    if(p.kur_isvesti==1)
    {
    isvedimasFun(p, nuskriaustukai, "nuskriaustukai.txt", vard_size, pav_size);
    if(p.koks_konteineris == 1 || p.koks_konteineris == 3)
    isvedimasFun(p, kietiakai, "kietiakai.txt", vard_size, pav_size);
    else if(p.koks_konteineris == 2)
    isvedimasFun(p, studentai, "kietiakai.txt", vard_size, pav_size);
    }
    if(p.kur_isvesti==1)
    cout<<dydis<<" Surusiuotu studentu isvedimas i du failus uztruko: "<<fixed<<setprecision(4)<<t3.elapsed()<<" s"<<endl;

    //Laiko skaiciavimo pabaiga:
    auto end2 = high_resolution_clock::now(); // Skaiciavimo pabaiga
    duration<double> diff2 = end2-start2; // Skaiciuojame skirtuma
    duration<double> diffFinal = diff+diff1+diff2;
    // if(p.choice==4)
    // cout<<"Programos vykdymo laikas: "<<diffFinal.count()<<" s\n"<<endl;
    return 0;
}
