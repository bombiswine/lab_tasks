/*
    Author: Merson Alexandr

    Group: ���-001-O-01

    Task#: 1.9

    Description: ������� ������, �������� � ��, � ����� � ���������.
*/

#include <stdio.h>

int main()
{
    //����������, �������� ����� � ��, �, �� ��������������
    double lengthCm, lengthM, lengthKm;

    printf("\n This program converts the length entered in cm to m and km");

    //�������� ������������ ��������� ������������� ��������
     // ����������� ����������� ����
    int input_var_amont = 0;
    int input_value_is_integer = 0;
    do {
        printf("\n Please enter the length in centimeters: ");
        input_var_amont = scanf("%lf", &lengthCm );
        input_value_is_integer = input_var_amont == 1;
        if(!input_value_is_integer) {
            printf("\n Input error: input value must be integer!");
            fflush(stdin); //����� ������� �����
        }
    } while(!input_value_is_integer);
    //�����������
    lengthM = lengthCm / 100;
    lengthKm = lengthM / 1000;
    //����� ���������� �� �����
    printf("\n Length in meters: %f \n Length in kilometers: %f \n", lengthM, lengthKm);

    return 0;
}
