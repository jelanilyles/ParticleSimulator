function [] = msdComp(fname1,fname2,fname3,fname4,fname5,fname6,fname7,fname8,fname9,fname10,fname11,fname12,fname13,fname14,fname15,fname16,fname17,fname18,fname19,fname20,fname21,fname22,fname23,fname24)


% folder = 'MSDTexts';
% fname = fullfile(folder,fname);
% gname = fullfile(folder,gname);
% hname = fullfile(folder,hname);
% 
% fid = fopen(fname);
% gid = fopen(gname);
% hid = fopen(hname);
% 
% scan1 = textscan(fid, '%f');
% scan2 = textscan(gid, '%f');
% scan3 = textscan(hid, '%f');
% 
% file1 = scan1{1,1};
% file2 = scan2{1,1};
% file3 = scan3{1,1};


loglog(fname1,'-','Color','b','LineWidth',1);
hold on;
loglog(fname2,'-','Color','g','LineWidth',1);
loglog(fname3,'-','Color','r','LineWidth',1);
loglog(fname4,'-.','Color','b','LineWidth',1);
loglog(fname5,'-.','Color','g','LineWidth',1);
loglog(fname6,'-.','Color','r','LineWidth',1);
loglog(fname7,'--','Color','b','LineWidth',1);
loglog(fname8,'--','Color','g','LineWidth',1);
loglog(fname9,'--','Color','r','LineWidth',1);
loglog(fname10,':','Color','b','LineWidth',1);
loglog(fname11,':','Color','g','LineWidth',1);
loglog(fname12,':','Color','r','LineWidth',1);
loglog(fname13,'-','Color','c','LineWidth',1);
loglog(fname14,'-','Color','y','LineWidth',1);
loglog(fname15,'-','Color','m','LineWidth',1);
loglog(fname16,'-.','Color','c','LineWidth',1);
loglog(fname17,'-.','Color','y','LineWidth',1);
loglog(fname18,'-.','Color','m','LineWidth',1);
loglog(fname19,'--','Color','c','LineWidth',1);
loglog(fname20,'--','Color','y','LineWidth',1);
loglog(fname21,'--','Color','m','LineWidth',1);
loglog(fname22,':','Color','c','LineWidth',1);
loglog(fname23,':','Color','y','LineWidth',1);
loglog(fname24,':','Color','m','LineWidth',1);


% loglog(fname4,'Color','c','LineWidth',1);

% plot(fname5,'-.','Color','b','LineWidth',1);
% plot(fname6,'-.','Color','c','LineWidth',1);
% plot(fname7,'-.','Color','y','LineWidth',1);
% plot(fname8,'-.','Color','m','LineWidth',1);


