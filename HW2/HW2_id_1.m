load('inputdata')
M = [packet,zeros(1,32)];
C = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
remainder = [];
for i = 1 : 12000
    if M(i) == 1
        remainder(1:32) = xor(M(i+1:i+32), C(2:33));
        M(i+1:i+32) = remainder(1:32);
    end
end
codepacket = [packet(1:12000),M(12001:12032)];
save('id.mat','codepacket');