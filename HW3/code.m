load('network_A.mat')

dis=zeros(1,100); %% distance from node 1
par=zeros(1,100); %% record the parent of a node

for i=1:100
    if(A(1,i)==1)
        dis(1,i)=1;
        par(1,i)=1;
    end
end

for d=2:100   
    for j=1:100
        if(dis(1,j)==d-1)
               for i=1:100
                   if(A(j,i)==1 && par(1,i)==0)
                       dis(1,i)=d;
                       par(1,i)=j;
                   end
               end
        end
    end
end

tree=zeros(100,100);
for i=1:100
    tree(i,par(1,i))=1;
    tree(par(1,i),i)=1;
end

save('result.mat','tree'); %%save tree



