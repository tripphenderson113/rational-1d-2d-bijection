import os
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

numerList = []
denomList = []
dAxisList = []

maxL = 51

# Get the directory where this script is located
baseDir = os.path.dirname(__file__)
filePath = os.path.join(baseDir, "iterationFile")

#Set up distance-from-axis data
with open(filePath) as iterFile:
    iterFile.readline()
    for line in range(maxL + 1):
        line = iterFile.readline()
        numerList.append(float(line.split("       ")[1]))
        denomList.append(float(line.split("       ")[2]))
        dAxisList = [float(numer) / float(denom) for numer, denom in zip(numerList, denomList)]

# Extra graph
    # plt.plot(denomList,numerList, 'o-')
    # plt.xlabel("Denominator")
    # plt.ylabel("Numerator")
    # plt.title("2D: Distance From Furthest Axis")
    # plt.show()

#1D value
l = 0.0

# figure setup
fig, ax = plt.subplots()
ax.set_xlim(-7.5, 7.5)
ax.set_ylim(-7.5, 7.5)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_aspect('equal', adjustable='box')

#Draw boxes from distance-from-axis data
pathList = [[]]
for dAxis in dAxisList:
    pathList.append([[0,dAxis,dAxis,dAxis,0,-dAxis,-dAxis,-dAxis,0],[dAxis,dAxis,0,-dAxis,-dAxis,-dAxis,0,dAxis,dAxis]])
pathList.pop(0)

#Interpolate between box data points
def makeXPiece(x1x2,frac):
    x = (1 - frac) * x1x2[0] + frac * x1x2[1]
    # print(x)
    return x
def makeYPiece(y1y2,frac):
    y = (1 - frac) * y1y2[0] + frac * y1y2[1]
    # print(y)
    return y

#Prepare 100 objects, title, text box, and two dots
lines = []
for _ in range(maxL + 8):
    line, = ax.plot([],[],color='red')
    lines.append(line)
ax.plot(0,0,'bo')
dot, = ax.plot([],[],'ro')
title = ax.set_title(r"Bijective 2D->1D:" + "   " + r"$Q^2$($R^1$)," + "  " + "0 ≤ $R^1$ < " + str(maxL))
textBox = ax.text(0.02, 0.95, "L = 0.00", transform = ax.transAxes,  fontsize=12,verticalalignment='top',bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.5))

#Choose lines given R
def plotZeroToL(R): #R is just l, but clarifies it's any real number
    #Draw complete boxes
    maxIntR = int(R)
    for intR in range(maxIntR + 1):
        lines[intR].set_data(pathList[intR][0],pathList[intR][1])
        lines[intR].set_color('blue')
    if R % 1 != 0:
        #Draw eighths of final box
        eigths = int((float(R) % 1) / 0.125)
        lines[maxIntR].set_data(pathList[maxIntR][0][0:eigths + 1],pathList[maxIntR][1][0:eigths + 1])
        lines[maxIntR].set_color('red')
        #Draw less than eigth of final box
        finalPieceLen = (float(R) % 1) % 0.125
        finalPieceX1 = pathList[maxIntR][0][eigths]
        finalPieceX2 = makeXPiece(pathList[maxIntR][0][eigths:eigths + 2],finalPieceLen / 0.125)
        finalPieceY1 = pathList[maxIntR][1][eigths]
        finalPieceY2 = makeYPiece(pathList[maxIntR][1][eigths:eigths + 2],finalPieceLen / 0.125)
        lines[maxIntR + 1].set_data([finalPieceX1,finalPieceX2],[finalPieceY1,finalPieceY2])
        lines[maxIntR + 1].set_color('red')
        dot.set_data([finalPieceX2],[finalPieceY2])
        print(str(R) + ": [" + str(finalPieceX2) + ", " + str(finalPieceY2) + "]")
    #Draw text box
    textBox.set_text(f"L = {R:.2f}")
    #reset when frames are at start
    if R < 1:
        for line in lines:
                line.set_data([], [])
    return lines + [dot, textBox]

#Choose R given frame, call plotZeroToL
def update(frame):
    L = maxL*float(frame + 1)/float(1001)
    return plotZeroToL(L)
    
ani = FuncAnimation(fig, update, frames=1001, interval = 5, blit=True) #blit false for smoother zooming and movement
plt.show()