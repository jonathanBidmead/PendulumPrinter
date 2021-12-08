function thetaRef = Kinematics(cartPath)

r1 = 160;
r2 = 180;
t = length(cartPath);
epsilon = 1;

% refX = linspace(0.1,1,t);
% refY = linspace(0.1,1,t);
% 
% refX = linspace(0,1.5,t);
% refY = 1.*sin(2.*refX);

refX = cartPath(:,1);
refY = cartPath(:,2);


theta2 = acos((refX.^2 + refY.^2 - r1^2 - r2^2)/(2*r1*r2));
% theta1 = atan(refY./refX) - atan((r2.*sin(theta2))./(r1+r2.*cos(theta2)));
piece1 = atan(refY./refX);
piece2 = atan((r2.*sin(theta2))./(r1+r2.*cos(theta2)));
%accounting for things looping around
for i = 1:length(piece1)
    if (piece1(i) > 0)
        piece1(i) = piece1(i) - pi;
    end
    if (piece2(i) < 0)
        piece2(i) = piece2(i) - pi;
    end
    
end

theta1 = piece1 - piece2;

%0.371718 and -2.76628

% for i = 1:length(theta2)
%     if (theta2(i) > 0)
%         theta2(i) = theta2(i) - pi;
%     end
%     
% end

% tiledlayout(2,1);
% nexttile;
% plot(atan(refY./refX));
% nexttile;
% plot(atan((r2.*sin(theta2))./(r1+r2.*cos(theta2))));


thetaRef(:,1) = theta1;
thetaRef(:,2) = theta2;


end

