# Author: Phillip Jones
# Date: 08/19/2022, updated 05/25/2023, updated 07/13/2023
# Description: Simple client for sending/recieveing information using a UART interface, or Network Socket
#              to either a mock CyBot server, or the actual CyBot

# General Python tutorials (W3schools):  https://www.w3schools.com/python/

import numpy as np
import matplotlib.pyplot as plt
import os  # import function for finding absolute path to this python script
# Serial library:  https://pyserial.readthedocs.io/en/latest/shortintro.html 
# import serial  # If using UART option (i.e., using a physical cable), then make sure serial library has been installed, and uncomment this line.
import time # Time library   
# Socket library:  https://realpython.com/python-sockets/  
# See: Background, Socket API Overview, and TCP Sockets  
import socket   

absolute_path = os.path.dirname(__file__) # Absoult path to this python script
relative_path = "./"   # Path to sensor data file relative to this python script (./ means data file is in the same directory as this python script)
full_path = os.path.join(absolute_path, relative_path) # Full path to sensor data file
filename = 'sensor-scan.txt' # Name of file you want to store sensor data from your sensor scan command


# Choose to create either a UART or TCP port socket to communicate with Cybot (Not both!!: I.e, comment out the one not being used)
# UART BEGIN
#cybot = serial.Serial('COM100', 115200)  # UART (Make sure you are using the correct COM port and Baud rate!!)
# UART END

# TCP Socket BEGIN (See Echo Client example): https://realpython.com/python-sockets/#echo-client-and-server
HOST = "192.168.1.1"  # The server's hostname or IP address
PORT = 288        # The port used by the server
cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
                      
cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
# TCP Socket END

# Send some text: Either 1) Choose "Hello" or 2) have the user enter text to send
# send_message = "Hello\n"                            # 1) Hard code message to "Hello", or

fig = None
send_message = input("Enter a message:") + '\n'   # 2) Have user enter text

cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server

print("Sent to server: " + send_message) 

# Send messges to server until user sends "quit"
#while send_message != 'quit\n':
 #       print("wait for server reply\n")
  #      rx_message = cybot.readline()      # Wait for a message, readline expects message to end with "\n"
   #     print("Got a message from server: " + rx_message.decode() + "\n") # Convert message from bytes to String (i.e., decode)
    #    send_message = input("Enter a message (enter quit to exit):") + '\n' # Enter next message to send to server
     #   cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server

#angle_degrees = []
#angle_radians = []
#distance = []
# Send messges to server until user sends "quit"
while send_message != 'quit':

        cybot.write(b"h")
        print("Requested Sensor scan from Cybot:\n")

        angle_degrees = [] 
        angle_radians = []
        distance = []
        rahh = 0

        rx_message = ""
        file_object = open(full_path + filename,'w')
        #file_object.write("Degrees Distance(cm)\n")
        while not rx_message.endswith("END\n"):
                rx_bytes = cybot.readline()
                rx_message.encode().strip()
                file_object.write(rx_message + "\n")
                print(rx_message.decode())
                #print(rahh)
                #rahh += 1
                data = rx_message.split()
                #if len(data) > 0 and data[0] == "Degress (cm)":

                angle_degrees = np.array(angle_degrees)
                distance_plot = np.minimum(np.array(distance), 100)

                if fig is None or not plt.fignum_exists(fig.number):
                        fig, ax = plt.subplots(subplot_kw={'projection' : 'polar'})
                ax.clear()

                ax.plot(angle_degrees, distance, color='r', linewidth=4.0)  # Plot distance verse angle (in radians), using red, line width 4.0
                ax.set_xlabel('Distance (m)', fontsize = 14.0)  # Label x axis
                ax.set_ylabel('Angle (degrees)', fontsize = 14.0) # Label y axis
                ax.xaxis.set_label_coords(0.5, 0.15) # Modify location of x axis label (Typically do not need or want this)
                ax.tick_params(axis='both', which='major', labelsize=14) # set font size of tick labels
                ax.set_rmax(1200)                    # Saturate distance at 2.5 meters
                ax.set_rticks([0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200])   # Set plot "distance" tick marks at .5, 1, 1.5, 2, and 2.5 meters
                ax.set_rlabel_position(-22.5)     # Adjust location of the radial labels
                ax.set_thetamax(180)              # Saturate angle to 180 degrees
                ax.set_xticks(np.arange(0,np.pi+.1,np.pi/4)) # Set plot "angle" tick marks to pi/4 radians (i.e., displayed at 45 degree) increments
                                             # Note: added .1 to pi to go just beyond pi (i.e., 180 degrees) so that 180 degrees is displayed
                ax.grid(True)                     # Show grid lines

        # # Create title for plot (font size = 14pt, y & pad controls title vertical location)
                ax.set_title("Polar Plot of CyBot Sensor Scan from 0 to 180 Degrees", size=14, y=1.0, pad=-24) 
                plt.show()  # Display plot



                
                #print("                  rah")
                        
                #elif len(data) == 2:
                        #try:
                                #print("                 (1")
                                #angle_degrees.append(float(data[0]))
                                #distance.append(float(data[1]))
                        #except ValueError:
                                #print("                 (2")
                                #pass
        #if len(angle_degrees) > 0:
                
                #file_object = open(full_path + filename,'w')
                #file_object.write("Distance Distance(cm)\n")

                #for i in range(len(angle_degrees)):
                        #file_object.write(str(angle_degrees[i]) + " " + str(distance[i]) + "\n")
        # if(rx_message.endswith("END\n")):
        #         file_object.close()

                # angle_degrees = np.array(angle_degrees)
                # distance_plot = np.minimum(np.array(distance), 100)

                # if fig is None or not plt.fignum_exists(fig.number):
                #         fig, ax = plt.subplots(subplot_kw={'projection' : 'polar'})
                # ax.clear()

                # ax.plot(angle_degrees, distance, color='r', linewidth=4.0)  # Plot distance verse angle (in radians), using red, line width 4.0
                # ax.set_xlabel('Distance (m)', fontsize = 14.0)  # Label x axis
                # ax.set_ylabel('Angle (degrees)', fontsize = 14.0) # Label y axis
                # ax.xaxis.set_label_coords(0.5, 0.15) # Modify location of x axis label (Typically do not need or want this)
                # ax.tick_params(axis='both', which='major', labelsize=14) # set font size of tick labels
                # ax.set_rmax(1200)                    # Saturate distance at 2.5 meters
                # ax.set_rticks([0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200])   # Set plot "distance" tick marks at .5, 1, 1.5, 2, and 2.5 meters
                # ax.set_rlabel_position(-22.5)     # Adjust location of the radial labels
                # ax.set_thetamax(180)              # Saturate angle to 180 degrees
                # ax.set_xticks(np.arange(0,np.pi+.1,np.pi/4)) # Set plot "angle" tick marks to pi/4 radians (i.e., displayed at 45 degree) increments
                #                              # Note: added .1 to pi to go just beyond pi (i.e., 180 degrees) so that 180 degrees is displayed
                # ax.grid(True)                     # Show grid lines

        # # Create title for plot (font size = 14pt, y & pad controls title vertical location)
                ax.set_title("Polar Plot of CyBot Sensor Scan from 0 to 180 Degrees", size=14, y=1.0, pad=-24) 
                plt.show()  # Display plot

        send_message = input("Enter a message (enter quit to exit):") + '\n'


print("Client exiting, and closing file descriptor, and/or network socket\n")
time.sleep(2) # Sleep for 2 seconds

cybot.close()         # Close file object associated with the socket or UART
cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)







