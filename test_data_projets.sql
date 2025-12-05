-- Additional test data for project statistics demonstration
-- This script adds more diverse projects to showcase the statistics functionality

-- Insert additional projects with different types and payment methods
INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, ID_CLIENT, PAIMENT, MONTANT, MATRIEL) 
VALUES (333, 'live', TO_DATE('2024-01-15', 'YYYY-MM-DD'), TO_DATE('2024-01-30', 'YYYY-MM-DD'), NULL, 'virement', 15000, 'Équipement live streaming');

INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, ID_CLIENT, PAIMENT, MONTANT, MATRIEL) 
VALUES (444, 'live', TO_DATE('2024-02-10', 'YYYY-MM-DD'), TO_DATE('2024-02-25', 'YYYY-MM-DD'), NULL, 'cash', 8500, 'Caméras et micros');

INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, ID_CLIENT, PAIMENT, MONTANT, MATRIEL) 
VALUES (555, 'podcast', TO_DATE('2024-03-05', 'YYYY-MM-DD'), TO_DATE('2024-03-20', 'YYYY-MM-DD'), NULL, 'chèque', 12000, 'Studio d\'enregistrement');

INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, ID_CLIENT, PAIMENT, MONTANT, MATRIEL) 
VALUES (666, 'live', TO_DATE('2024-04-01', 'YYYY-MM-DD'), TO_DATE('2024-04-15', 'YYYY-MM-DD'), NULL, 'virement', 22000, 'Équipement complet événement');

INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, ID_CLIENT, PAIMENT, MONTANT, MATRIEL) 
VALUES (777, 'podcast', TO_DATE('2024-05-10', 'YYYY-MM-DD'), TO_DATE('2024-05-25', 'YYYY-MM-DD'), NULL, 'cash', 5500, 'Matériel audio');

INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, ID_CLIENT, PAIMENT, MONTANT, MATRIEL) 
VALUES (888, 'live', TO_DATE('2024-06-15', 'YYYY-MM-DD'), TO_DATE('2024-06-30', 'YYYY-MM-DD'), NULL, 'chèque', 18000, 'Production vidéo en direct');

INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, ID_CLIENT, PAIMENT, MONTANT, MATRIEL) 
VALUES (999, 'podcast', TO_DATE('2024-07-01', 'YYYY-MM-DD'), TO_DATE('2024-07-15', 'YYYY-MM-DD'), NULL, 'virement', 9500, 'Studio podcast professionnel');

-- This will give us the following distribution:
-- Types: 
-- - podcast: 5 projects (28888 + 222 + 12000 + 5500 + 9500 = 56110 DT)
-- - live: 4 projects (15000 + 8500 + 22000 + 18000 = 63500 DT)
--
-- Payment methods:
-- - virement: 4 projects (28888 + 15000 + 22000 + 9500 = 75388 DT)  
-- - cash: 3 projects (222 + 8500 + 5500 = 14222 DT)
-- - chèque: 2 projects (12000 + 18000 = 30000 DT)
--
-- Total: 9 projects, 119610 DT total, average 13290 DT per project