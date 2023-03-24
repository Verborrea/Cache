import matplotlib.pyplot as plt

x = range(100, 1501, 100)
classic = [.0047, .04, .14, .36, .73, 1.16, 1.9, 3, 4.6, 6.5, 10.5, 14.1, 18.6, 23.8, 26.8]
blocks = [.005, .033, .128, .29, .55, .97, 1.6, 2.3, 3.5, 4.7, 6.1, 7.9, 10.2, 12.4, 15.5]

line1, = plt.plot(x, classic, label='Clásico')
line2, = plt.plot(x, blocks, label='Bloques*')
plt.legend(handles=[line1, line2])

plt.ylabel('Segundos')
plt.xlabel('Dimensiones')
plt.grid()
plt.show()