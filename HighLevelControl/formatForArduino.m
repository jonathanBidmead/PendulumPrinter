
clc
disp("//theta2")
fprintf("const float refPos [%d]= ",length(theta2))
fprintf('{')
for i = 1:length(theta2)-1
    fprintf("%4.4f, ",theta2(i))
end
fprintf('%4.4f};\n',theta2(end))