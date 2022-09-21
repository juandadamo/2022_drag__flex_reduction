def f_acquire(b=1):
    archivo = open('output.txt','w')
    fsampling = 80
    dt = 1/fsampling
    tventana = 8
    tiempo_total,valores = np.zeros((2,fsampling*tventana))
    valores[valores==0] = np.NaN
    arduino = serial.Serial(port, 115200, timeout=None)
    i = 0
    time0 = time.time()
    time1 = time.time()-time0
    linea = arduino.readline() 
    while time1<tventana:
        linea = arduino.readline()   # read a '\n' terminated line

        texto = str(linea.decode('ascii')).split('\r')[0]
        
        if texto!= '\n':
            if texto != '':
                data = float(texto)                
                if i ==0:
                    time0 = time.time()
                     
                time1 = time.time()-time0
                tiempo_total[i] = time1
                valores[i] = data
                i += 1
                line.set_data([tiempo_total,valores])
                fig.canvas.draw()
                archivo.write(f'{time1:.4f},{data:.2f}\n')
    arduino.close()
    archivo.close()
    return tiempo_total,valores

def f_save(b=1):
    nombre = f'B_{rigidez_i.value:03d}_L_{int(longitud_i.value*100):03d}.txt'
    if os.path.isfile(nombre):
        nombre = np.sort(glob.glob(nombre[:3]+'*'))[-1]
        partes = nombre.split('_')
        if len(partes)<5:
            numfile = 0
            nombre = nombre.replace(f'.txt',f'_{numfile:0d}.txt') 
        else:
            numfile = int(nombre.split('.txt')[0][-1:])
            nombre = nombre.replace(f'_{numfile:0d}.txt',f'_{numfile+1:0d}.txt')   
    print(nombre)
    os.rename('output.txt',nombre)
    
    
    
