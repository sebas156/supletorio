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
    string tipo;
    string placa;
    char Tparqueadero;
    int piso, celda, BanderaParqueado,TipoDeCobro;
};

#endif // VEHICULO_H
