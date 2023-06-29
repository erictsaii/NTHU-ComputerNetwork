C = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
r = [];

for i = 1 : 12029
    for j = 1 : 17 : 12030
        for k = 1 : 48: 12031
            for l = 2 : 2934 : 12032
               error = zeros(1,12032);
               error(i) = 1; 
               error(j) = 1; 
               error(k) = 1; 
               error(l) = 1;
               for x = 1 : 12000
                   if error(x) == 1
                       r(1:32) = xor(error(x+1:x+32), C(2:33));
                       error(x+1:x+32) = r(1:32);
                   end
               end
               if sum(r) == 0
                   break;
               end
            end
            if sum(r) == 0
                break;
            end
        end
        if sum(r) == 0
            break;
        end
    end
    if sum(r) == 0
        break;
    end
end

error=zeros(1,12032);
error(i)=1;
error(j)=1;
error(k)=1;
error(l)=1;
save('id.mat',"error","-append")








