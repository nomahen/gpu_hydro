import numpy as np
global x,y,z,rho,velx,vely,velz,pres,eint,gamc,game

def read_data(filename,nx,ny,nz):
    global x,y,z,rho,velx,vely,velz,pres,eint,gamc,game
    nvar = 11
    
    data = open(filename,"r")
    parsed_data = []
    for line in data:
        parsed_data.append(np.array(line.split()).astype(float))
    parsed_data = np.array(parsed_data)
    
    # Save global arrays for x,y,z and each of the 8 NVAR (see config.h)                         
    x = np.reshape(parsed_data[:,0],(nx,ny,nz))
    y = np.reshape(parsed_data[:,1],(nx,ny,nz))
    z = np.reshape(parsed_data[:,2],(nx,ny,nz))
    rho = np.reshape(parsed_data[:,3],(nx,ny,nz))
    velx = np.reshape(parsed_data[:,4],(nx,ny,nz))
    vely = np.reshape(parsed_data[:,5],(nx,ny,nz))
    velz = np.reshape(parsed_data[:,6],(nx,ny,nz))
    pres = np.reshape(parsed_data[:,7],(nx,ny,nz))
    eint = np.reshape(parsed_data[:,8],(nx,ny,nz))
    gamc = np.reshape(parsed_data[:,9],(nx,ny,nz))
    game = np.reshape(parsed_data[:,10],(nx,ny,nz))
                            
    return