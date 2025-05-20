#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estructura para los productos
typedef struct Producto {
    char nombre[100];
    float costo;
    struct Producto* siguiente;
} Producto;

// Estructura para el usuario
typedef struct Usuario {
    char nombre[100];
    char numeroCelular[15];
    float totalPagar;
    Producto* carrito; // Apuntador al inicio de la lista de carrito de compras
} Usuario;

// Función para crear un nuevo producto
Producto* crearProducto(char* nombre, float costo) {
    Producto* nuevo = (Producto*)malloc(sizeof(Producto));
    if (nuevo == NULL) {
        printf("Error al asignar memoria para el producto.\n");
        exit(1);
    }
    
    strcpy(nuevo->nombre, nombre);
    nuevo->costo = costo;
    nuevo->siguiente = NULL;
    
    return nuevo;
}

// Función para cargar los productos desde un archivo
Producto* cargarProductos(const char* archivo) {
    FILE* f = fopen(archivo, "r");
    if (f == NULL) {
        printf("Error al abrir el archivo %s.\n", archivo);
        return NULL;
    }
    
    Producto* inicio = NULL;
    Producto* ultimo = NULL;
    char nombre[100];
    float costo;
    
    while (fscanf(f, "%99[^,],%f\n", nombre, &costo) == 2) {
        Producto* nuevo = crearProducto(nombre, costo);
        
        if (inicio == NULL) {
            inicio = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }
    
    fclose(f);
    return inicio;
}

// Función para agregar un producto al carrito
void agregarAlCarrito(Usuario* usuario, Producto* productoSeleccionado) {
    if (productoSeleccionado == NULL) {
        printf("No se ha seleccionado ningún producto.\n");
        return;
    }
    
    Producto* nuevoEnCarrito = crearProducto(productoSeleccionado->nombre, productoSeleccionado->costo);
    
    // Actualizamos el total a pagar
    usuario->totalPagar += productoSeleccionado->costo;
    
    // Agregamos el producto al carrito
    if (usuario->carrito == NULL) {
        usuario->carrito = nuevoEnCarrito;
    } else {
        Producto* temp = usuario->carrito;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoEnCarrito;
    }
    
    printf("¡Producto agregado al carrito!\n");
}

// Función para mostrar información del usuario
void mostrarInfoUsuario(Usuario* usuario) {
    printf("\n=== Información del Usuario ===\n");
    printf("Nombre: %s\n", usuario->nombre);
    printf("Número de celular: %s\n", usuario->numeroCelular);
    printf("Total a pagar: $%.2f\n", usuario->totalPagar);
}

// Función para mostrar el carrito de compras
void mostrarCarrito(Usuario* usuario) {
    printf("\n=== Mi Carrito de Compras ===\n");
    
    if (usuario->carrito == NULL) {
        printf("El carrito está vacío. Regresa al menú principal para agregar productos.\n");
        return;
    }
    
    Producto* temp = usuario->carrito;
    int contador = 1;
    float total = 0;
    
    while (temp != NULL) {
        printf("%d. %s - $%.2f\n", contador, temp->nombre, temp->costo);
        total += temp->costo;
        temp = temp->siguiente;
        contador++;
    }
    
    printf("\nTotal a pagar: $%.2f\n", total);
}

// Función para navegar por la lista de productos
void navegarProductos(Usuario* usuario, Producto* listaProductos) {
    if (listaProductos == NULL) {
        printf("No hay productos disponibles.\n");
        return;
    }
    
    Producto* actual = listaProductos;
    char opcion;
    
    while (1) {
        system("clear"); // Para sistemas Unix/Linux
        // En Windows, usar: system("cls");
        
        printf("\n=== Lista de Productos ===\n");
        printf("Producto actual: %s - $%.2f\n\n", actual->nombre, actual->costo);
        printf("Opciones:\n");
        printf("A - Producto anterior\n");
        printf("S - Siguiente producto\n");
        printf("C - Agregar al carrito\n");
        printf("V - Volver al menú principal\n");
        printf("Ingrese su opción: ");
        
        scanf(" %c", &opcion);
        opcion = toupper(opcion); // Convertimos a mayúscula
        
        switch (opcion) {
            case 'A':
                // Producto anterior
                if (actual != listaProductos) {
                    // Encontramos el nodo anterior
                    Producto* temp = listaProductos;
                    while (temp->siguiente != actual) {
                        temp = temp->siguiente;
                    }
                    actual = temp;
                } else {
                    printf("Ya estás en el primer producto.\n");
                    getchar(); // Esperar a que el usuario presione una tecla
                    getchar();
                }
                break;
                
            case 'S':
                // Siguiente producto
                if (actual->siguiente != NULL) {
                    actual = actual->siguiente;
                } else {
                    printf("Ya estás en el último producto.\n");
                    getchar(); // Esperar a que el usuario presione una tecla
                    getchar();
                }
                break;
                
            case 'C':
                // Agregar al carrito
                agregarAlCarrito(usuario, actual);
		printf("\nPresiona Enter para continuar...");                
		getchar(); // Esperar a que el usuario presione una tecla
                getchar();
                break;
                
            case 'V':
                // Volver al menú principal
                return;
                
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                getchar(); // Esperar a que el usuario presione una tecla
                getchar();
        }
    }
}

// Función para liberar la memoria de una lista de productos
void liberarLista(Producto* inicio) {
    Producto* temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->siguiente;
        free(temp);
    }
}

int main() {
    // Creamos un usuario
    Usuario usuario;
    strcpy(usuario.nombre, "Cliente");
    strcpy(usuario.numeroCelular, "1234567890");
    usuario.totalPagar = 0.0;
    usuario.carrito = NULL;
    
    // Cargamos los productos desde el archivo
    Producto* listaProductos = cargarProductos("productos.txt");
    if (listaProductos == NULL) {
        printf("No se pudieron cargar los productos. Asegúrate de que el archivo 'productos.txt' existe.\n");
        return 1;
    }
    
    int opcion;
    
    // Solicitamos la información del usuario
    printf("Bienvenido a la Tienda\n");
    printf("Ingresa tu nombre: ");
    scanf("%99s", usuario.nombre);
    printf("Ingresa tu número de celular: ");
    scanf("%14s", usuario.numeroCelular);
    
    // Menú principal
    while (1) {
        system("clear"); // Cambiado a "clear" para sistemas Unix/Linux
        // En Windows, usar: system("cls");
        
        printf("\n=== Tienda - Menú Principal ===\n");
        printf("1. Ver mi carrito de compras\n");
        printf("2. Ver mi información de usuario\n");
        printf("3. Ver la lista de productos\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");
        
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                mostrarCarrito(&usuario);
                printf("\nPresiona Enter para continuar...");
                getchar(); // Consumir el salto de línea
                getchar(); // Esperar a que el usuario presione Enter
                break;
                
            case 2:
                mostrarInfoUsuario(&usuario);
                printf("\nPresiona Enter para continuar...");
                getchar(); // Consumir el salto de línea
                getchar(); // Esperar a que el usuario presione Enter
                break;
                
            case 3:
                navegarProductos(&usuario, listaProductos);
		printf("\nPresiona Enter para continuar...");
                break;
                
            case 4:
                printf("¡Hasta pronto!\n");
                // Liberamos la memoria antes de salir
                liberarLista(listaProductos);
                liberarLista(usuario.carrito);
                return 0;
                
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                getchar(); // Consumir el salto de línea
                getchar(); // Esperar a que el usuario presione Enter
        }
    }
    
    return 0;
}

