#include <stdio.h>
#include <string.h>

#define NUM_ZONAS 2
#define DIAS_HISTORICOS 2

#define LIMITE_CO2_OMS (10.0 * DIAS_HISTORICOS / 30.0)
#define LIMITE_SO2_OMS (20.0 * DIAS_HISTORICOS / 30.0)
#define LIMITE_NO2_OMS (40.0 * DIAS_HISTORICOS / 30.0)
#define LIMITE_PM25_OMS (25.0 * DIAS_HISTORICOS / 30.0)

#define LIMITE_CO2_ACTUAL 50.0
#define LIMITE_SO2_ACTUAL 20.0
#define LIMITE_NO2_ACTUAL 40.0
#define LIMITE_PM25_ACTUAL 25.0

typedef struct
{
    char nombre[50];
    float nivelesActuales[4]; /* CO2, SO2, NO2, PM2.5*/
    float historicos[DIAS_HISTORICOS][4];
    float prediccion[4];
} Zona;

void ingresarDatosIniciales(Zona[], int *datosIngresados);
void ingresarDatosHistoricos(Zona[], int *datosHistoricosIngresados);
void monitorearActual(Zona[], int datosIngresados);
void predecirContaminacion(Zona[], int datosHistoricosIngresados);
void calcularPromedios(Zona[], int datosHistoricosIngresados);
void emitirAlertas(Zona[], int datosIngresados, int datosHistoricosIngresados);
void generarRecomendaciones(Zona[], int datosIngresados, int datosHistoricosIngresados);
void exportarReporte(Zona[], int datosIngresados, int datosHistoricosIngresados);

int main()
{
    Zona zonas[NUM_ZONAS];
    int datosIngresados = 0;
    int datosHistoricosIngresados = 0;

    int opcion;
    do
    {
        printf("\nSistema Integral de Gestión y Predicción de Contaminación del Aire\n");
        printf("1. Ingresar datos iniciales\n");
        printf("2. Ingresar datos históricos\n");
        printf("3. Monitorear niveles actuales\n");
        printf("4. Predecir niveles futuros\n");
        printf("5. Calcular promedios históricos y compararlos con la OMS\n");
        printf("6. Emitir alertas preventivas\n");
        printf("7. Generar recomendaciones\n");
        printf("8. Exportar reporte\n");
        printf("9. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            ingresarDatosIniciales(zonas, &datosIngresados);
            break;
        case 2:
            ingresarDatosHistoricos(zonas, &datosHistoricosIngresados);
            break;
        case 3:
            monitorearActual(zonas, datosIngresados);
            break;
        case 4:
            predecirContaminacion(zonas, datosHistoricosIngresados);
            break;
        case 5:
            calcularPromedios(zonas, datosHistoricosIngresados);
            break;
        case 6:
            emitirAlertas(zonas, datosIngresados, datosHistoricosIngresados);
            break;
        case 7:
            generarRecomendaciones(zonas, datosIngresados, datosHistoricosIngresados);
            break;
        case 8:
            exportarReporte(zonas, datosIngresados, datosHistoricosIngresados);
            break;
        case 9:
            printf("Saliendo del sistema. ¡Hasta luego!\n");
            break;
        default:
            printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 9);

    return 0;
}

void ingresarDatosIniciales(Zona zonas[], int *datosIngresados)
{
    for (int i = 0; i < NUM_ZONAS; i++)
    {
        printf("\nIngrese el nombre de la zona %d: ", i + 1);
        fgets(zonas[i].nombre, sizeof(zonas[i].nombre), stdin);
        zonas[i].nombre[strcspn(zonas[i].nombre, "\n")] = '\0';

        printf("Ingrese el nivel de CO2 para la zona %s: ", zonas[i].nombre);
        scanf("%f", &zonas[i].nivelesActuales[0]);
        getchar();

        printf("Ingrese el nivel de SO2 para la zona %s: ", zonas[i].nombre);
        scanf("%f", &zonas[i].nivelesActuales[1]);
        getchar();

        printf("Ingrese el nivel de NO2 para la zona %s: ", zonas[i].nombre);
        scanf("%f", &zonas[i].nivelesActuales[2]);
        getchar();

        printf("Ingrese el nivel de PM2.5 para la zona %s: ", zonas[i].nombre);
        scanf("%f", &zonas[i].nivelesActuales[3]);
        getchar();
    }
    *datosIngresados = 1;
    printf("\nDatos iniciales ingresados correctamente.\n");
}

void ingresarDatosHistoricos(Zona zonas[], int *datosHistoricosIngresados)
{
    for (int i = 0; i < NUM_ZONAS; i++)
    {
        printf("\nIngresando datos históricos para la zona %s:\n", zonas[i].nombre);
        for (int d = 0; d < DIAS_HISTORICOS; d++)
        {
            printf("Día %d:\n", d + 1);
            printf("  CO2: ");
            scanf("%f", &zonas[i].historicos[d][0]);
            printf("  SO2: ");
            scanf("%f", &zonas[i].historicos[d][1]);
            printf("  NO2: ");
            scanf("%f", &zonas[i].historicos[d][2]);
            printf("  PM2.5: ");
            scanf("%f", &zonas[i].historicos[d][3]);
        }
    }
    *datosHistoricosIngresados = 1;
    printf("\nDatos históricos ingresados correctamente.\n");
}

void monitorearActual(Zona zonas[], int datosIngresados)
{
    if (datosIngresados == 0)
    {
        printf("No se puede monitorear sin ingresar datos iniciales.\n");
        return;
    }

    for (int i = 0; i < NUM_ZONAS; i++)
    {
        printf("\nZona: %s\n", zonas[i].nombre);
        printf("  CO2: %.2f\n", zonas[i].nivelesActuales[0]);
        printf("  SO2: %.2f\n", zonas[i].nivelesActuales[1]);
        printf("  NO2: %.2f\n", zonas[i].nivelesActuales[2]);
        printf("  PM2.5: %.2f\n", zonas[i].nivelesActuales[3]);

        if (zonas[i].nivelesActuales[0] > LIMITE_CO2_ACTUAL)
            printf("  Alerta: El nivel de CO2 excede el límite permitido de %.2f.\n", LIMITE_CO2_ACTUAL);
        if (zonas[i].nivelesActuales[1] > LIMITE_SO2_ACTUAL)
            printf("  Alerta: El nivel de SO2 excede el límite permitido de %.2f.\n", LIMITE_SO2_ACTUAL);
        if (zonas[i].nivelesActuales[2] > LIMITE_NO2_ACTUAL)
            printf("  Alerta: El nivel de NO2 excede el límite permitido de %.2f.\n", LIMITE_NO2_ACTUAL);
        if (zonas[i].nivelesActuales[3] > LIMITE_PM25_ACTUAL)
            printf("  Alerta: El nivel de PM2.5 excede el límite permitido de %.2f.\n", LIMITE_PM25_ACTUAL);
    }
}

void predecirContaminacion(Zona zonas[], int datosHistoricosIngresados)
{
    if (datosHistoricosIngresados == 0)
    {
        printf("No se puede predecir sin datos históricos ingresados.\n");
        return;
    }

    printf("\nPredicción de niveles de contaminación:\n");
    for (int i = 0; i < NUM_ZONAS; i++)
    {
        printf("Zona: %s\n", zonas[i].nombre);
        for (int j = 0; j < 4; j++)
        {
            float suma = 0;
            for (int d = 0; d < DIAS_HISTORICOS; d++)
            {
                suma += zonas[i].historicos[d][j];
            }
            zonas[i].prediccion[j] = ((suma / DIAS_HISTORICOS)*DIAS_HISTORICOS)/30;
        }

        printf("  Predicción CO2: %.2f\n", zonas[i].prediccion[0]);
        printf("  Predicción SO2: %.2f\n", zonas[i].prediccion[1]);
        printf("  Predicción NO2: %.2f\n", zonas[i].prediccion[2]);
        printf("  Predicción PM2.5: %.2f\n", zonas[i].prediccion[3]);

        if (zonas[i].prediccion[0] > LIMITE_CO2_ACTUAL)
        {
            printf("  Alerta: Predicción de CO2 excede el límite permitido de %.2f.\n", LIMITE_CO2_ACTUAL);
        }
        if (zonas[i].prediccion[1] > LIMITE_SO2_ACTUAL)
        {
            printf("  Alerta: Predicción de SO2 excede el límite permitido de %.2f.\n", LIMITE_SO2_ACTUAL);
        }
        if (zonas[i].prediccion[2] > LIMITE_NO2_ACTUAL)
        {
            printf("  Alerta: Predicción de NO2 excede el límite permitido de %.2f.\n", LIMITE_NO2_ACTUAL);
        }
        if (zonas[i].prediccion[3] > LIMITE_PM25_ACTUAL)
        {
            printf("  Alerta: Predicción de PM2.5 excede el límite permitido de %.2f.\n", LIMITE_PM25_ACTUAL);
        }
    }
}

void calcularPromedios(Zona zonas[], int datosHistoricosIngresados)
{
    if (datosHistoricosIngresados==0)
    {
        printf("No se puede calcular promedios sin datos históricos ingresados.\n");
        return;
    }

    printf("\nPromedios históricos comparados con límites OMS:\n");
    for (int i = 0; i < NUM_ZONAS; i++)
    {
        printf("Zona: %s\n", zonas[i].nombre);
        float promedios[4] = {0};

        for (int j = 0; j < 4; j++)
        {
            for (int d = 0; d < DIAS_HISTORICOS; d++)
            {
                promedios[j] += zonas[i].historicos[d][j];
            }
            promedios[j] /= DIAS_HISTORICOS;
        }

        printf("  Promedio CO2: %.2f (Límite OMS: %.2f)\n", promedios[0], LIMITE_CO2_OMS);
        printf("  Promedio SO2: %.2f (Límite OMS: %.2f)\n", promedios[1], LIMITE_SO2_OMS);
        printf("  Promedio NO2: %.2f (Límite OMS: %.2f)\n", promedios[2], LIMITE_NO2_OMS);
        printf("  Promedio PM2.5: %.2f (Límite OMS: %.2f)\n", promedios[3], LIMITE_PM25_OMS);
    }
}

void emitirAlertas(Zona zonas[], int datosIngresados, int datosHistoricosIngresados)
{
    if (datosIngresados==0 || datosHistoricosIngresados==0)
    {
        printf("No se pueden emitir alertas sin datos iniciales e históricos.\n");
        return;
    }

    printf("\nAlertas preventivas:\n");
    for (int i = 0; i < NUM_ZONAS; i++)
    {
        printf("Zona: %s\n", zonas[i].nombre);
        int alertaEmitida = 0;

        if (zonas[i].nivelesActuales[0] > LIMITE_CO2_OMS)
        {
            printf("  Alerta: CO2 excede el límite permitido.\n");
            alertaEmitida = 1;
        }
        if (zonas[i].nivelesActuales[1] > LIMITE_SO2_OMS)
        {
            printf("  Alerta: SO2 excede el límite permitido.\n");
            alertaEmitida = 1;
        }
        if (zonas[i].nivelesActuales[2] > LIMITE_NO2_OMS)
        {
            printf("  Alerta: NO2 excede el límite permitido.\n");
            alertaEmitida = 1;
        }
        if (zonas[i].nivelesActuales[3] > LIMITE_PM25_OMS)
        {
            printf("  Alerta: PM2.5 excede el límite permitido.\n");
            alertaEmitida = 1;
        }

        if (!alertaEmitida)
        {
            printf("  Todos los niveles están dentro de los límites aceptables.\n");
        }
    }
}

void generarRecomendaciones(Zona zonas[], int datosIngresados, int datosHistoricosIngresados)
{
    if (datosIngresados==0 || datosHistoricosIngresados==0)
    {
        printf("No se pueden generar recomendaciones sin datos iniciales e históricos.\n");
        return;
    }

    printf("\nRecomendaciones para reducir contaminación:\n");
    for (int i = 0; i < NUM_ZONAS; i++)
    {
        printf("Zona: %s\n", zonas[i].nombre);

        if (zonas[i].nivelesActuales[0] > LIMITE_CO2_OMS)
        {
            printf("  Reducir emisiones de CO2: promover transporte público y energías renovables.\n");
        }
        if (zonas[i].nivelesActuales[1] > LIMITE_SO2_OMS)
        {
            printf("  Reducir emisiones de SO2: mejorar combustibles industriales.\n");
        }
        if (zonas[i].nivelesActuales[2] > LIMITE_NO2_OMS)
        {
            printf("  Reducir emisiones de NO2: optimizar sistemas de transporte.\n");
        }
        if (zonas[i].nivelesActuales[3] > LIMITE_PM25_OMS)
        {
            printf("  Reducir partículas PM2.5: regular actividades de construcción y quema de biomasa.\n");
        }
    }
}

void exportarReporte(Zona zonas[], int datosIngresados, int datosHistoricosIngresados)
{
    if (datosIngresados==0 || datosHistoricosIngresados==0)
    {
        printf("No se puede exportar un reporte sin datos iniciales e históricos.\n");
        return;
    }

    FILE *reporte = fopen("reporte_contaminacion.txt", "w");
    if (reporte==NULL)
    {
        printf("Error al crear el archivo de reporte.\n");
        return;
    }

    fprintf(reporte, "Reporte de Contaminación del Aire\n\n");

    for (int i = 0; i < NUM_ZONAS; i++)
    {
        fprintf(reporte, "Zona: %s\n", zonas[i].nombre);
        fprintf(reporte, "Niveles actuales:\n");
        fprintf(reporte, "  CO2: %.2f\n", zonas[i].nivelesActuales[0]);
        fprintf(reporte, "  SO2: %.2f\n", zonas[i].nivelesActuales[1]);
        fprintf(reporte, "  NO2: %.2f\n", zonas[i].nivelesActuales[2]);
        fprintf(reporte, "  PM2.5: %.2f\n", zonas[i].nivelesActuales[3]);

        fprintf(reporte, "Predicciones:\n");
        fprintf(reporte, "  CO2: %.2f\n", zonas[i].prediccion[0]);
        fprintf(reporte, "  SO2: %.2f\n", zonas[i].prediccion[1]);
        fprintf(reporte, "  NO2: %.2f\n", zonas[i].prediccion[2]);
        fprintf(reporte, "  PM2.5: %.2f\n", zonas[i].prediccion[3]);
    }

    fclose(reporte);
    printf("Reporte exportado exitosamente a 'reporte_contaminacion.txt'.\n");
}
