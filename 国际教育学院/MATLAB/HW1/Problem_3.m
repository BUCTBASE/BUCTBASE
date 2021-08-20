clear all
close all
clc

%   Create File
fid = fopen('Problem3_Result.txt', 'wt');
payment=1199.11;

%	Calculate  Balance
Balance_End =repmat(200000,1, 360);
Balance_Begin=repmat(0, 1, 360);
Balance_Begin(1)=Balance_End(1)*1.005;
Balance_End(1)= Balance_Begin(1)-payment;
for month = 2:360
    Balance_Begin(month)=Balance_End(month-1)*1.005;
    Balance_End(month)=Balance_Begin(month)-payment;
end

%   Write File
fprintf (fid,'      Beginning         Ending \n');
fprintf (fid,'Month Balence   Payment Balance \n');
fprintf (fid,'===== ========= ======= ======= \n');
for month = 1:360
    if month<=12
        fprintf (fid,'%5i %-9.2f%8.2f%10.2f\n',month,Balance_Begin(month),payment,Balance_End(month));
    end
    if month==359
        fprintf (fid,'\n\n\n');
    end
    if month>=359
        fprintf (fid,'%5i %-9.2f%8.2f%10.2f\n',month,Balance_Begin(month),payment,Balance_End(month));
    end
end
fprintf(fid,'\nFinal balance to be refunded = %.2f\n',Balance_End(month));
fclose(fid);
