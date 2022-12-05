% load random=0.3
BLG1(7,10,2)=0;
BLG1(1,:,:)=load("../result/plot_BLG1_10_10.dat");
BLG1(2,:,:)=load("../result/plot_BLG1_20_20.dat");
BLG1(3,:,:)=load("../result/plot_BLG1_40_40.dat");
BLG1(4,:,:)=load("../result/plot_BLG1_80_80.dat");
BLG1(5,:,:)=load("../result/plot_BLG1_160_160.dat");
BLG1(6,:,:)=load("../result/plot_BLG1_320_320.dat");
BLG1(7,:,:)=load("../result/plot_BLG1_640_640.dat");

NG1(7,10,2)=0;
NG1(1,:,:)=load("../result/plot_NG1_10_10.dat");
NG1(2,:,:)=load("../result/plot_NG1_20_20.dat");
NG1(3,:,:)=load("../result/plot_NG1_40_40.dat");
NG1(4,:,:)=load("../result/plot_NG1_80_80.dat");
NG1(5,:,:)=load("../result/plot_NG1_160_160.dat");
NG1(6,:,:)=load("../result/plot_NG1_320_320.dat");
NG1(7,:,:)=load("../result/plot_NG1_640_640.dat");

LDG1(7,10,2)=0;
LDG1(1,:,:)=load("../result/plot_LDG1_10_10.dat");
LDG1(2,:,:)=load("../result/plot_LDG1_20_20.dat");
LDG1(3,:,:)=load("../result/plot_LDG1_40_40.dat");
LDG1(4,:,:)=load("../result/plot_LDG1_80_80.dat");
LDG1(5,:,:)=load("../result/plot_LDG1_160_160.dat");
LDG1(6,:,:)=load("../result/plot_LDG1_320_320.dat");
LDG1(7,:,:)=load("../result/plot_LDG1_640_640.dat");

blg1(7,2)=0;
ng1(7,2)=0;
ldg1(7,2)=0;

for i = 1 : 7
    blg1(i,:)= mean(BLG1(i,:,:),2);
    ng1(i,:)= mean(NG1(i,:,:),2);
    ldg1(i,:)= mean(LDG1(i,:,:),2);
end
% % plot weight
% x=[10 20 40 80 160 320 640];
% hold on;
% plot(x,blg1(:,1),'-r',"LineWidth",2);
% plot(x,ng1(:,1),'-g',"LineWidth",2);
% plot(x,ldg1(:,1),'-b',"LineWidth",2);
% legend("Baseline Greedy(BLG)", "Naive Greedy(NG)", "Linear Deterministic Greedy(LDG)");
% xlabel("Matrix Size N × N");
% ylabel("Weights ERROR");

% plot edge
x=[10 20 40 80 160 320 640];
hold on;
plot(x,blg1(:,2),'-r',"LineWidth",2);
plot(x,ng1(:,2),'-g',"LineWidth",2);
plot(x,ldg1(:,2),'-b',"LineWidth",2);
legend("Baseline Greedy(BLG)", "Naive Greedy(NG)", "Linear Deterministic Greedy(LDG)");
xlabel("Matrix Size N × N");
ylabel("Edges ERROR");

