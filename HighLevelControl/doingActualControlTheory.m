motorTF = tf([0.5],[0.5 1]);
motorSS = ss(motorTF);
A = motorSS.A;
B = motorSS.B;
C = motorSS.C;
D = motorSS.D;

t = 10;

Abar = [0 C;0 A];
Bbar = [0;B];

K = place(Abar,Bbar,[-5,-2])

Kr = K(1)
Kx = K(2)

simInput = [linspace(0,10,length(y1))',y1];
