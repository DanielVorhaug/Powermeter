import matplotlib.pyplot as plt
import matplotlib.animation as animation
import datetime

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

def animate(i):
    f = open("blink.csv", "r")

    dates = []

    for x in f:
        dates.append(x.split(","))

    f.close()

    for x in dates:
        x[-1] = (x[-1].split("\n"))[0]

    for i in range(len(dates)):
        for j in range(len(dates[i])):
            dates[i][j] = int(dates[i][j])
    
    time = []
    power = []
    
    for i in range(len(dates)-1):
        time.append((dates[i][3]+ dates[i+1][3]) * 1800000000 + (dates[i][4] + dates[i+1][4]) * 30000000 + (dates[i][5]+dates[i+1][5]) * 500000 + (dates[i][6] + dates[i+1][6])/2)
        power.append(1800000000/((dates[i+1][3]- dates[i][3]) * 3600000000 + (dates[i+1][4] - dates[i][4]) * 60000000 + (dates[i+1][5]-dates[i][5]) * 1000000 + dates[i+1][6] - dates[i][6]))
    
    #max = 0
    #theX = 0
    #for x in range(len(power)):
        #if power[x] > max:
            #max = power[x]
            #theX = x
    #print(dates[theX])
        
    #totalPower = 0
    #for x in range(len(power)):
        #totalPower += (power * ((dates[i+1][3]- dates[i][3]) * 3600000000 + (dates[i+1][4] - dates[i][4]) * 60000000 + (dates[i+1][5]-dates[i][5]) * 1000000 + dates[i+1][6] - dates[i][6]))
    #print("Total power used from blinks: " + str(len(power)) + ", from powerestimate: " + str(totalpower))
    
    ax1.clear()
    ax1.plot(time, power)
    

ani = animation.FuncAnimation(fig, animate, interval=10000)
plt.show()

#plt.plot(time, power)
#plt.show()

