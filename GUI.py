import tkinter as tk #Se importan las librerias a usar
import serial
import struct
import time

while(1): #Se inicializa la conexion con el puerto
    while(1):
        try:
            numero = str(int(input(">  COM: ")))
            port = "com" + numero
            break
        except:
            print ("Enter a numeric value")
    try:
        data = serial.Serial(port, baudrate = 9600, timeout=1500)
        break
    except:
        print("Unable to open port")

Main = tk.Tk() #Se crea la vetana principal y sus caracteristicas
Main.title("Comunicación serial")
w = 500 
h = 200

ws = Main.winfo_screenwidth()
hs = Main.winfo_screenheight()

x = (ws/2) - (w/2)
y = (hs/2) - (h/2)

Main.geometry('%dx%d+%d+%d' % (w, h, x, y))
Main.resizable(0,0)
Main. config (background = "Black")

com = tk.Label(Main, text = "COM:" + numero, bg = "black", fg = "white", font = ("Times New Roman", 24)) #Label que muestra el COM utilizado
com.pack()

data.write(struct.pack('>B',0))


def getSensor(): #Funcion para leer el puerto continuamente
    if ord(data.read()) == 255: #Verificar y ordenar datos
        s1 = ord(data.read())
        s2 = ord(data.read())

        sensor1 = round(s1 * 5/255, 2)
        sensor2 = round(s2 * 5/255, 2)

        sensor1 = str(sensor1) + "V"
        sensor2 = str(sensor2) + "V"
            
        POT01.set(sensor1) #Definir el valor al texto variable de un label
        POT02.set(sensor2)
    Main.after(10, getSensor) #Tiempo en ms que se ejecuta esta funcion

def enviar (): #Función para enviar datos
    try: #Prueba que sea un número entero
        entero = int(read3.get())
        error.set(" ")
        
        if entero > 255 or entero < 0: #Verifica que este dentro del rango si no, muestra un error
            error.set("INGRESE UN VALOR ENTRE 0 Y 255")

        else: #Si todo se cumple, envia el dato
            data.write(struct.pack('>B',entero))
        
    except: #Si no es entero, muestra un error
        print ("ingrese un numero")
        error.set("INGRESE UN VALOR NUMÉRICO ENTERO")   

name1 = tk.Label(Main, text = "POT01", bg = "black", fg = "white", font = ("Times New Roman", 14)) #Label de titulos
name1.place(x = 75, y = 50)

name2 = tk.Label(Main, text = "POT02", bg = "black", fg = "white", font = ("Times New Roman", 14))
name2.place(x = 220, y = 50)

name3 = tk.Label(Main, text = "TTL", bg = "black", fg = "white", font = ("Times New Roman", 14))
name3.place(x = 365, y = 50)

POT01 = tk.StringVar() #Declaracion de variable para texto
POT01.set("0")

read1 = tk.Label(Main, textvariable = POT01, bg = "black", fg = "white", font = ("OCR A Extended", 14)) #Label de texto variable para los pots
read1.place(x = 75, y = 100)

POT02 = tk.StringVar()
POT02.set("0")

read2 = tk.Label(Main, textvariable = POT02, bg = "black", fg = "white", font = ("OCR A Extended", 14))
read2.place(x = 220, y = 100)

sensor3 = tk.StringVar()
sensor3.set("000")

read3 = tk.Entry(Main, font = ("OCR A Extended", 14), width = 3)
read3.place(x = 365, y = 100)

send = tk.Button(Main, text = "Enviar", command = enviar) #Boton enlazado con la funcion enviar
send.place(x = 365, y = 150)

error = tk.StringVar()
error.set(" ")

warning = tk.Label(Main, textvariable = error, bg = "black", fg = "red", font = ("Times New Roman", 8))
warning.place(x = 140, y = 150)

Main.after(10, getSensor)

Main.mainloop()
