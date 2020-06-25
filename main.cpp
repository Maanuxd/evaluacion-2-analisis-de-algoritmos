#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/**
 * @param argc cantidad de argumentos
 * @param argv argumentos
 */

struct alumno{
        int rut = 0;
        float NEM = 0;
        float ranking = 0;
        float puntmate = 0;
        float puntleng = 0;
        float puntcs = 0;
        float punthis = 0;
        float promML = 0;

        bool operator < (const alumno &promedio) const{
            return promML > promedio.promML;
        }
};

struct Carrera{
        int lugar = 0;
        string nombre;
        string codigo;
        float pond_NEM = 0;
        float pond_ranking = 0;
        float pond_mate = 0;
        float pond_leng = 0;
        float pond_cs = 0;
        float pond_his = 0;
        int vacantes = 0;
        float primer_mat = 0;
        float ultimo_mat = 0;

        bool operator < (const Carrera &pcorte) const{
            return ultimo_mat > pcorte.ultimo_mat;
        }
};

void corrector();
vector <alumno> ordenar_alumnos();
vector <Carrera> ordenar_carreras();
void crear_salidas(vector <Carrera>);
void designacion_carrera (vector<alumno>, vector <Carrera>);

vector<alumno> postulantes;
vector<Carrera> carreras;

int main() {
    
    //if (argc > 1){
        //ordenar archivos de admision(carreras) y puntajes(alumnos)
        
        corrector();
        
        ordenar_alumnos();
        
        //cout<<"tamaño real: "<<postulantes.size()<<endl;
        
        
        ordenar_carreras();
        
        cout<<"vacantes "<<carreras[3].nombre<<": "<<carreras[3].vacantes<<endl;
        cout<<"vacantes "<<carreras[5].nombre<<": "<<carreras[5].vacantes<<endl;
        cout<<"vacantes "<<carreras[17].nombre<<": "<<carreras[17].vacantes<<endl;
        cout<<"vacantes "<<carreras[19].nombre<<": "<<carreras[19].vacantes<<endl;
        crear_salidas(carreras);
        designacion_carrera(postulantes,carreras);
        
    //}   
    //else{
      //  cout<<"No ha ingresado una palabra"<<endl;
   // }
    
    return 0;
}

void corrector(){//--> Busca en el archivo admision-PSU.csv todas las , y las reemplaza por .
    ifstream archivo;
    string punto, aux, espacio;

    archivo.open("admision-PSU.csv");
    ofstream auxiliar("auxiliar.csv");

    if(archivo.fail()){
        std::cout<<"ERROR AL BUSCAR EL ARCHIVO"<<endl;
        exit(1);
    }
    else{
        punto =".";
        while(!archivo.eof()){
            
            getline(archivo,aux);
            int pos = aux.find(",");
            
            while (pos!=-1 ){
                aux.replace(pos,1,punto);
                pos = aux.find(",",pos + punto.size()); 
                
            }
            auxiliar<<aux<<endl;
        }
        archivo.close();
        auxiliar.close();
        remove("admision-PSU.csv");
        rename("auxiliar.csv","admision-PSU.csv");
    }
}
//funciones para ordenar
vector<alumno> ordenar_alumnos(){
    
    int linea,i;
    ifstream archivo;

    archivo.open("puntajes.csv");
    
    if(archivo.fail()){
        std::cout<<"No se pudo leer el archivo "<<endl;
        exit(1);
    }
    else{ std::cout<<"Se leera el archivo puntajes"<<endl;
        //leer archivo puntajes.csv e ingresa los datos en un struct
        for(i=0;!archivo.eof();i++){
            
            alumno postulante;
            string rut_alumno,nem,rnkg,mate,leng,cs,his;

            postulantes.push_back(alumno());
            linea = i;

            if (!archivo.eof()){
                getline(archivo,rut_alumno,';');
                istringstream(rut_alumno)>>postulantes[i].rut;

                getline(archivo,nem,';');
                istringstream(nem)>>postulantes[i].NEM;

                getline(archivo,rnkg,';');
                istringstream(rnkg)>>postulantes[i].ranking;

                getline(archivo,mate,';');
                istringstream(mate)>>postulantes[i].puntmate;

                getline(archivo,leng,';');
                istringstream(leng)>>postulantes[i].puntleng;
            
                getline(archivo,cs,';');
                istringstream(cs)>>postulantes[i].puntcs;

                getline(archivo,his,'\n');
                istringstream(his)>>postulantes[i].punthis;

            //define el promedio de matematicas y lenguaje para cda alumno del archivo
                postulantes[i].promML = (postulantes[i].puntmate + postulantes[i].puntleng)/2;
            }
        }
        //std::cout<<"Cantidad de postulados: "<<linea<<endl;
        postulantes.pop_back();
        //std::cout<<"tamaño vector: "<<postulantes.size()<<endl;        
    }
    
    archivo.close();

    //ordena el vector de mayor a menor segun promedio de matematicas y lenguaje
    std::sort(postulantes.begin(),postulantes.end());
    
    //std::cout<<"VECTOR ORDENADO Y WEA"<<endl;
    return postulantes;
}

vector<Carrera> ordenar_carreras(){

    int i=0,linea;
    ifstream archivo;

    archivo.open("admision-PSU.csv");
    
    if(archivo.fail()){
        std::cout<<"No se pudo leer el archivo"<<endl;
        exit(1);
    }
    else{ 
        std::cout<<"Se leera el archivo admision-PSU"<<endl;
        //leer archivo Admision-PSU.csv e ingresa los datos en un vector de struct
        while(!archivo.eof()){
            
            Carrera carrera;
            string lugar, nombre_carrera,codigo_carrera,nem,ranking,p_mate,p_leng,p_cs,p_his,
            promML,PMP,vacantes,primero,ultimo;

            carreras.push_back(Carrera());

            getline(archivo,lugar,';');
            carreras[i].lugar = i+1;

            getline(archivo,carreras[i].nombre,';');

            getline(archivo,codigo_carrera,';');
            istringstream(codigo_carrera)>>carreras[i].codigo;
            
            getline(archivo,nem,';');
            istringstream(nem)>>carrera.pond_NEM;
            carreras[i].pond_NEM = carrera.pond_NEM/100;
            
            getline(archivo,ranking,';');
            istringstream(ranking)>>carrera.pond_ranking;
            carreras[i].pond_ranking = carrera.pond_ranking/100;

            getline(archivo,p_leng,';');
            istringstream(p_leng)>>carrera.pond_leng;
            carreras[i].pond_leng = carrera.pond_leng/100;

            getline(archivo,p_mate,';');
            istringstream(p_mate)>>carrera.pond_mate;
            carreras[i].pond_mate = carrera.pond_mate/100;
            
            getline(archivo,p_cs,';');
            istringstream(p_cs)>>carrera.pond_cs;
            carreras[i].pond_cs = carrera.pond_cs/100;

            carreras[i].pond_his = carreras[i].pond_cs;

            getline(archivo,promML,';');

            getline(archivo,PMP,';');

            getline(archivo,vacantes,';');
            istringstream(vacantes)>>carreras[i].vacantes;

            getline(archivo,primero,';');
            istringstream(primero)>>carreras[i].primer_mat;

            getline(archivo,ultimo,'\n');
            istringstream(ultimo)>>carreras[i].ultimo_mat;
                
            if(!archivo.eof()){
                i++;
            }
        }
        //std::cout<<"N° de carreras disponibles: "<<i<<endl;
        carreras.pop_back();       
    }
    
    archivo.close();

    //ordena el vector de mayor a menor segun ultimo puntaje de ingreso 2019
    std::sort(carreras.begin(),carreras.end());
    
    for (int j=0; j<carreras.size();j++){
        std::cout<<"\n"<<j+1<<" "<<carreras[j].nombre<<endl;
        std::cout<<"codigo: "<<carreras[j].codigo<<endl;
        std::cout<<"vacantes disponibles: "<<carreras[j].vacantes<<endl;
    }
    
    return carreras;
    std::cout<<"\nVECTOR CARRERAS ORDENADO Y WEA"<<"\n"<<endl;
}

void crear_salidas(vector <Carrera> carreras){//crear archivos.txt para cada carrera
    //recorrer vector carreras, y en cada iteracion cear un archivo.txt de 
    //nombre=codigo.carrera
    std::cout<<"a renombrar"<<endl;
    string nombre_archivo;

    for(int i=0; i<carreras.size();i++){
        nombre_archivo=carreras[i].codigo;
        nombre_archivo+=".txt";
        ofstream archivo;

        archivo.open(nombre_archivo.c_str(),ios::out);
        archivo.close();
    }
    std::cout<<"\nHecho"<<endl;
}

void designacion_carrera(vector<alumno> postulantes, vector <Carrera> carreras){
    //tomar primer alumno y recorrer vector carreras
    //al recorrer cada parte del vector carreras, revisar si quedan cupos,
    //si quedan cupos,sacar promedio con la ponderaciones, caso contrario, 
    //pasar a la siguiente carrera
    //la carrera donde tenga mayor promedio sera a la que postule 
    //ingresar los datos al archivo de salida correspondiente
    //hacer lo mismo con cada elemento del vector de postulantes
    int i,j,k,cont; 
    ofstream archivo;

    for (i=0;i<postulantes.size();i++){
        string nombre_archivo;
        int rut_aux=0,lugar=0;
        float p_postulacion, prom_mayor=0, p_NEM, p_ranking, p_mate, p_leng, p_historia, p_ciencias;
        
        if(postulantes[i].promML < 450){
                std::cout<<postulantes[i].rut<<" no cumple los requisitos para postular"<<endl;
                i++;
        }
        else{
            for(j=0;j<carreras.size();j++){
                if(carreras[j].vacantes <= 0){
                    j++;   
                    k++;
                    if(k<=28){
                        cout<<"No quedan mas cupos en la UTEM"<<endl;
                        break; 
                    }
                }   
            
                else{
                    p_NEM = postulantes[i].NEM * carreras[j].pond_NEM;
                    p_ranking = postulantes[i].ranking * carreras[j].pond_ranking;
                    p_mate = postulantes[i].puntmate * carreras[j].pond_mate;
                    p_leng = postulantes[i].puntleng * carreras[j].pond_leng;
                    p_historia = postulantes[i].punthis * carreras[j].pond_his;
                    p_ciencias = postulantes[i].puntcs * carreras[j].pond_cs;
                
                    if(p_ciencias >= p_historia){
                        p_postulacion = p_NEM + p_ranking + p_mate + p_leng + p_ciencias;
                    }
                    else{
                        p_postulacion = p_NEM + p_ranking + p_mate + p_leng + p_historia;
                    }

                    if(p_postulacion >= prom_mayor){
                        prom_mayor = p_postulacion;
                        rut_aux = postulantes[i].rut;
                        lugar = j;
                    }
                    else{
                        j++;
                    }   
                }
                    
            }//aqui se cierra el for que recorre las carreras
        }

        if (prom_mayor>0){
            nombre_archivo = carreras[lugar].codigo;
            nombre_archivo+=".txt";

            archivo.open(nombre_archivo.c_str(),ios::app);

            if(archivo.fail()){
                std::cout<<"No se pudo abrir el archivo "<<endl;
                exit(1);
            }
            else{
                archivo<<"Rut: "<<postulantes[i].rut<<endl;
                archivo<<"puntaje de postulacion: "<<prom_mayor<<endl;
                archivo.close();
                carreras[lugar].vacantes --;
                if (carreras[lugar].vacantes==0){
                    cout<<"no quedan vacantes en:  "<<carreras[lugar].codigo<<endl;
                    j++;
                }
                
        
                
                if(k<=28){
                    cout<<"No quedan mas cupos en la u"<<endl;
                    break; 
                }
            }    
        }
        else{
            break;
        }
        //Hasta aca llega le for que recorre los alumnos    
    }
    
}
