# ProyectoFinal-C

# 🛒 Tiendita en C

Este proyecto consiste en el desarrollo de una aplicación en lenguaje C que simula el funcionamiento básico de una **tiendita**, integrando conceptos clave de programación estructurada, manejo de archivos, estructuras y memoria dinámica.

## 📋 Descripción General

La aplicación está dividida en dos módulos principales:

1. **Gestión de Usuarios**
2. **Gestión de Productos**

Los usuarios pueden visualizar productos disponibles, seleccionar los que desean comprar y agregarlos a un carrito de compras personal. Toda la información de productos se carga desde un archivo `.txt` al iniciar el programa.

## 🎯 Objetivos

* Aplicar estructuras en C para modelar usuarios y productos.
* Utilizar listas ligadas para representar la lista de productos y el carrito de compras.
* Manejar archivos `.txt` para cargar la información de productos.
* Aplicar el uso de punteros y memoria dinámica.

---

## 🧾 Funcionalidades

Al ejecutar el programa, se muestra un menú con las siguientes opciones:

* 👤 **Ver mi información de usuario**
  Muestra el nombre, número de celular y total acumulado en el carrito.

* 🛍️ **Ver mi carrito de compras**
  Muestra los productos agregados al carrito. Si está vacío, se indicará.

* 📦 **Ver la lista de productos**
  Carga los productos desde un archivo `.txt`, permite navegar entre ellos con las teclas:

  * `S` → siguiente producto
  * `A` → producto anterior
    Además, se puede **agregar el producto actual al carrito**.


## 🛠️ Implementación Técnica

* Los productos se cargan desde un archivo `.txt` al iniciar la opción correspondiente.
* Se utiliza una lista ligada doblemente enlazada para navegar entre productos con facilidad.
* Al agregar un producto al carrito, se crea una **copia** del nodo y se inserta en la lista del carrito.
* La aplicación se mantiene activa hasta que el usuario elija salir.

---

## 📂 Archivos

* `tienda.c` — Archivo principal con el menú e integración general.
* `productos.txt` — Archivo de texto con la lista de productos.

---

## 👨‍💻 Autor

* Desarrollado por Deissy Jovita Hernandez 
* PROTECSA - UNAM
* Proyecto final de programación estructurada en lenguaje C.
