/* Creating new table "Price". */
CREATE TABLE "Price" AS
SELECT id, price, weekly_price, monthly_price, security_deposit, cleaning_fee, guests_included, extra_people, minimum_nights, maximum_nights, minimum_minimum_nights, maximum_minimum_nights, minimum_maximum_nights, maximum_maximum_nights, minimum_nights_avg_ntm, maximum_nights_avg_ntm
FROM "Listings";

/* Update the needed columns. */
UPDATE "Price"
SET price = REPLACE (REPLACE (price, '$', ''), ',' , '');

/* Update the column "weekly_price" */
UPDATE "Price"
SET weekly_price = REPLACE (REPLACE (price, '$', ''), ',' , '');

/* Update the column "monthly_price" */
UPDATE "Price"
SET monthly_price = REPLACE (REPLACE (price, '$', ''), ',' , '');

/* Update the column "security_deposit" */
UPDATE "Price"
SET security_deposit = REPLACE (REPLACE (price, '$', ''), ',' , '');

/* Update the column "cleaning_fee" */
UPDATE "Price"
SET cleaning_fee = REPLACE (REPLACE (price, '$', ''), ',' , '');

/*Update the column "extra_people" */
UPDATE "Price"
SET extra_people = REPLACE (REPLACE (price, '$', ''), ',' , '');

/* Change the type of the columns into numeric */
ALTER TABLE "Price"
ALTER COLUMN price TYPE INT USING price::numeric,
ALTER COLUMN weekly_price TYPE INT USING weekly_price::numeric, 
ALTER COLUMN monthly_price TYPE INT USING monthly_price::numeric,
ALTER COLUMN security_deposit TYPE INT USING security_deposit::numeric,
ALTER COLUMN cleaning_fee TYPE INT USING cleaning_fee::numeric,
ALTER COLUMN extra_people TYPE INT USING extra_people::numeric,
ALTER COLUMN minimum_nights_avg_ntm TYPE INT USING minimum_nights_avg_ntm::numeric,
ALTER COLUMN maximum_nights_avg_ntm TYPE INT USING maximum_nights_avg_ntm::numeric;

/*Rename column id to listing_id */
ALTER TABLE "Price" RENAME id TO listing_id; 

/* Dropping the columns that aren't needed anymore on "Copy_Listings" */
ALTER TABLE "Copy_Listings" DROP COLUMN price;
ALTER TABLE "Copy_Listings" DROP COLUMN weekly_price;
ALTER TABLE "Copy_Listings" DROP COLUMN monthly_price;
ALTER TABLE "Copy_Listings" DROP COLUMN security_deposit;
ALTER TABLE "Copy_Listings" DROP COLUMN cleaning_fee;
ALTER TABLE "Copy_Listings" DROP COLUMN guests_included;
ALTER TABLE "Copy_Listings" DROP COLUMN extra_people;
ALTER TABLE "Copy_Listings" DROP COLUMN minimum_nights;
ALTER TABLE "Copy_Listings" DROP COLUMN maximum_nights;
ALTER TABLE "Copy_Listings" DROP COLUMN minimum_minimum_nights;
ALTER TABLE "Copy_Listings" DROP COLUMN maximum_minimum_nights;
ALTER TABLE "Copy_Listings" DROP COLUMN minimum_maximum_nights;
ALTER TABLE "Copy_Listings" DROP COLUMN maximum_maximum_nights;
ALTER TABLE "Copy_Listings" DROP COLUMN minimum_nights_avg_ntm;
ALTER TABLE "Copy_Listings" DROP COLUMN maximum_nights_avg_ntm;

/* Setting primary and foreign keys where needed. */
ALTER TABLE "Price" ADD FOREIGN KEY (listing_id) REFERENCES "Copy_Listings"(id);
