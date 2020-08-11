#ifndef VEHICULO_H
#define VEHICULO_H
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

using std::chrono::system_clock;
using namespace std;

struct VariableTimepo{
    int dia;
    int hora;
    int minutos;
    int segundos;
};

class vehiculo
{
public:
    vehiculo();
    void SetBanderaParqueadero(int);
    int GetBanderaParqueadero();
    void SetCelda(int);
    void SetPiso(int);
    void SetTipoEstacionamiento(char);
    void SetPlacaVehiculo(string);
    void SetTipoVehiculo(string);
    int GetCelda();
    int GetPiso();
    char GetTipoEstacionamiento();
    string GetPlacaVehiculo();
    string GetTipoVehiculo();
    int GetTipoDeCobro();
    void SetTipoDeCobro(int);
    VariableTimepo Ingreso;
    VariableTimepo Salida;

private:
    string tipo; // Almacena el tipo de vehiculo: Carro, Moto o Bicleta.
    string placa;
    char Tparqueadero; // Almacena si el parqueadero es temporal o mensual.
    int piso;          // Almacena el tipo piso en el que se encuentra el vehiculo.
    int celda;         // Almacena la celda en la que se encuetra el veculo.
    int BanderaParqueado; // Esta bancera tiene dos valores 0 o 1. 0 significa que el vehiculo no está en el parqueadero.
                        // 1 que sí está.
    int TipoDeCobro; // puede ser 1 (por hora) 2 (por dia) 3 (mensual)
};

#endif // VEHICULO_H
