#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50

struct Producto {
   int id;
   char nombre[MAX_NOMBRE];
   char tipo[MAX_NOMBRE];
   int ubicacion;
   float precio;
   int cantidad;
   int cantidadComprada;
};

struct Producto producto[1000];
int totalProductos = 0;

void guardarProductos() {
    FILE* archivo = fopen("productos.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < totalProductos; i++) {
        fprintf(archivo, "%d|%s|%s|%d|%.2f|%d\n", producto[i].id, producto[i].nombre, producto[i].tipo, producto[i].ubicacion, producto[i].precio, producto[i].cantidad);
    }

    fclose(archivo);
}

void cargarProductos() {
    FILE* archivo = fopen("productos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    totalProductos = 0;

    while (fscanf(archivo, "%d|%[^|]|%[^|]|%d|%f|%d\n", &producto[totalProductos].id, producto[totalProductos].nombre, producto[totalProductos].tipo, &producto[totalProductos].ubicacion, &producto[totalProductos].precio, &producto[totalProductos].cantidad) == 6) {
        totalProductos++;
    }

    fclose(archivo);
}

void agregarProducto() {
    struct Producto nuevoProducto;
    int nuevoId;

    printf("Ingrese el nombre del Producto: ");
    scanf("%s", nuevoProducto.nombre);

    printf("Ingrese el tipo del Producto:\n");
    printf("====================================\n");
    printf("1) Lacteo\n");
    printf("2) Carne de Res\n");
    printf("3) Carne de Cerdo\n");
    printf("4) Carne de Pollo\n");
    printf("5) Otros\n");
    printf("====================================\n");
    scanf("%s", nuevoProducto.tipo);

    printf("Ingrese la ubicacion del Producto:\n");
    printf("====================================\n");
    printf("1) Freezer 1\n");
    printf("2) Freezer 2\n");
    printf("3) Freezer 3\n");
    printf("4) Freezer 4\n");
    printf("====================================\n");
    scanf("%d", &nuevoProducto.ubicacion);

    printf("Ingrese el precio del Producto: ");
    scanf("%f", &nuevoProducto.precio);

    printf("Ingrese la cantidad del Producto: ");
    scanf("%d", &nuevoProducto.cantidad);

    nuevoId = totalProductos + 1;

    for (int i = 0; i < totalProductos; i++) {
        if (producto[i].id == nuevoId) {
            nuevoId++;
            i = -1;
        }
    }

    nuevoProducto.id = nuevoId;

    producto[totalProductos++] = nuevoProducto;

    printf("\x1B[32m");
    printf("Producto agregado correctamente.\n");
    printf("\x1B[37m");

    guardarProductos();

    system("pause");
}

void buscarProducto() {
    char nombre[MAX_NOMBRE];

    printf("Ingrese el nombre del Producto a buscar: ");
    scanf("%s", nombre);

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(producto[i].nombre, nombre) == 0) {
            printf("ID: %d\n", producto[i].id);
            printf("Nombre: %s\n", producto[i].nombre);
            printf("Tipo: %s\n", producto[i].tipo);
            printf("Se ubica en el Freezer: %d\n", producto[i].ubicacion);
            printf("Precio en cordobas: %.2f\n", producto[i].precio);
            printf("Cantidad: %d\n", producto[i].cantidad);

            system("pause");
            return;
        }
    }
    printf("\x1B[31m");
    printf("Producto no encontrado.\n");

    system("pause");
}

void modificarProducto() {
    char nombre[MAX_NOMBRE];

    printf("Ingrese el nombre del Producto a modificar: ");
    scanf("%s", nombre);

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(producto[i].nombre, nombre) == 0) {
            printf("Ingrese el nuevo nombre del Producto: ");
            scanf("%s", producto[i].nombre);

            printf("Ingrese el nuevo tipo del Producto:\n");
            printf("====================================\n");
            printf("1) Lacteo\n");
            printf("2) Carne de Res\n");
            printf("3) Carne de Cerdo\n");
            printf("4) Carne de Pollo\n");
            printf("5) Otros\n");
            printf("====================================\n");
            scanf("%s", producto[i].tipo);

            printf("Ingrese el nuevo ubicacion del Producto:\n");
            printf("====================================\n");
            printf("1) Freezer 1\n");
            printf("2) Freezer 2\n");
            printf("3) Freezer 3\n");
            printf("4) Freezer 4\n");
            printf("====================================\n");
            scanf("%d", &producto[i].ubicacion);

            printf("Ingrese el nuevo precio del Producto: ");
            scanf("%f", &producto[i].precio);

            printf("Ingrese la nueva cantidad del Producto: ");
            scanf("%d", &producto[i].cantidad);

            printf("\x1B[32m");
            printf("Producto modificado correctamente.\n");
            printf("\x1B[37m");

            guardarProductos();

            system("pause");

            return;
        }
    }
    printf("\x1B[31m");
    printf("Producto no encontrado.\n");

    system("pause");
}

void pagarProducto() {
    char nombre[50];
    int cantidadp;
    float total = 0;
    int encontrado = 0;
    int carritoVacio = 1;

    do {
        printf("Ingrese el nombre del Producto que desea comprar (escriba '0' para finalizar): ");
        scanf("%s", nombre);

        if (strcmp(nombre, "0") != 0) {
            encontrado = 0;

            for (int i = 0; i < totalProductos; i++) {
                if (strcmp(producto[i].nombre, nombre) == 0) {
                    encontrado = 1;

                    printf("Usted seleccionó el producto: %s\n", producto[i].nombre);
                    printf("El precio del producto es: C$%.2f\n", producto[i].precio);

                    printf("Ingrese la cantidad que desea comprar: ");
                    scanf("%d", &cantidadp);

                    if (cantidadp <= 0) {
                        printf("La cantidad ingresada no es válida.\n");
                        break;
                    }

                    if (cantidadp > producto[i].cantidad) {
                        printf("No hay suficiente stock disponible para la cantidad deseada.\n");
                        break;
                    }

                    printf("Desea comprar %d unidades de %s? (S/N): ", cantidadp, producto[i].nombre);
                    char respuesta;
                    scanf(" %c", &respuesta);

                    if (respuesta == 'S' || respuesta == 's') {
                        float subtotal = producto[i].precio * cantidadp;
                        total += subtotal;

                        producto[i].cantidad -= cantidadp;
                        producto[i].cantidadComprada += cantidadp;

                        printf("\x1B[32m");
                        printf("Producto agregado al carrito de compras.\n");
                        printf("\x1b[33m");
                        printf("Subtotal: C$%.2f\n", subtotal);
                        printf("\x1B[37m");

                        carritoVacio = 0;
                    } else {
                        printf("No se realizó la compra del producto.\n");
                    }

                    break;
                }
            }

            if (!encontrado) {
                printf("\x1B[31m");
                printf("Producto no encontrado.\n");
            }
        }
    } while (strcmp(nombre, "0") != 0);

    if (!carritoVacio) {
        printf("\x1B[38;2;255;128;0m");
        printf("\nProductos en el carrito:\n");
        printf("\x1B[37m");
        for (int i = 0; i < totalProductos; i++) {
            if (producto[i].cantidadComprada > 0) {
                printf("\x1B[37m");
                printf("Nombre: %s\n", producto[i].nombre);
                printf("Precio unitario: C$%.2f\n", producto[i].precio);
                printf("Cantidad comprada: %d\n", producto[i].cantidadComprada);
                printf("==============================\n");
            }
        }
        printf("\x1B[32m");
        printf("Total a pagar: C$%.2f\n", total);
        printf("\x1B[37m");
        printf("==============================\n");
    } else {
        printf("\x1B[31m");
        printf("No se realizó ninguna compra.\n");
    }
    guardarProductos();
    system("pause");
}

void eliminarProducto() {
    char nombre[MAX_NOMBRE];

    printf("Ingrese el nombre del Producto a eliminar: ");
    scanf("%s", nombre);

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(producto[i].nombre, nombre) == 0) {
            for (int j = i; j < totalProductos - 1; j++) {
                producto[j] = producto[j + 1];
            }

            totalProductos--;
            printf("\x1B[32m");
            printf("Producto eliminado correctamente.\n");
            printf("\x1B[37m");
            guardarProductos();

            system("pause");

            return;
        }
    }
    printf("\x1B[31m");
    printf("Producto no encontrado.\n");

    system("pause");
}

void mostrarProductos() {
    
    printf("Productos registrados:\n");
    printf("==============================\n");

    for (int i = 0; i < totalProductos; i++) {
        printf("ID: %d\n", producto[i].id);
        printf("Nombre: %s\n", producto[i].nombre);
        printf("Tipo: %s\n", producto[i].tipo);
        printf("Ubicación: %d\n", producto[i].ubicacion);
        printf("Precio: %.2f\n", producto[i].precio);
        printf("Cantidad: %d\n", producto[i].cantidad);
        printf("==============================\n");
    }

    system("pause");
}

int main() {
    cargarProductos();

    int opcion;
    do {
        system("cls");
        printf("\x1b[33m");
        printf("Menu de opciones:\n");
        printf("1. Agregar Producto\n");
        printf("2. Buscar Producto\n");
        printf("3. Pagar Producto\n");
        printf("4. Modificar Producto\n");
        printf("5. Eliminar Producto\n");
        printf("6. Mostrar Productos\n");
        printf("7. Salir\n");
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcion);
        printf("\x1B[37m");
        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                buscarProducto();
                break;
            case 3:
                pagarProducto();
                break;
            case 4:
                modificarProducto();
                break;
            case 5:
                eliminarProducto();
                break;
            case 6:
                mostrarProductos();
                break;
            case 7:
                printf("\x1B[31m");
                printf("Saliendo del programa...\n");
                system("pause");
                return 0;
            default:
                printf("\x1B[31m");
                printf("Opcion no valida. Intente de nuevo.\n");
                system("pause");
                break;
        }
    } while (opcion != 7);

    return 0;
}
