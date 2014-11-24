mysqldump -u root -proot lab_estoque > lab_estoque.%date:/=-%.sql
"\Program Files\7-Zip\7z.exe" a lab_estoque.%date:/=-%.sql.7z lab_estoque.%date:/=-%.sql
del lab_estoque.24-11-2014.sql