/* Creating new table "Room". */
CREATE TABLE "Room" AS
SELECT id, accommodates, bathrooms, bedrooms, beds, bed_type,
amenities, square_feet, price, weekly_price, monthly_price, security_deposit FROM "Listings";

/* Renaming column on "Room". */
ALTER TABLE "Room" RENAME COLUMN "id" TO "listing_id";

/* Dropping the columns that aren't needed anymore on "Copy_Listings" */
ALTER TABLE "Copy_Listings" DROP COLUMN accommodates;
ALTER TABLE "Copy_Listings" DROP COLUMN bathrooms;
ALTER TABLE "Copy_Listings" DROP COLUMN bedrooms;
ALTER TABLE "Copy_Listings" DROP COLUMN beds;
ALTER TABLE "Copy_Listings" DROP COLUMN bed_type;
ALTER TABLE "Copy_Listings" DROP COLUMN amenities;
ALTER TABLE "Copy_Listings" DROP COLUMN square_feet;
ALTER TABLE "Copy_Listings" DROP COLUMN price;
ALTER TABLE "Copy_Listings" DROP COLUMN weekly_price;
ALTER TABLE "Copy_Listings" DROP COLUMN monthly_price;
ALTER TABLE "Copy_Listings" DROP COLUMN security_deposit;

/* Setting foreign key where needed. */
ALTER TABLE "Room" ADD FOREIGN KEY (listing_id) REFERENCES "Listings"(id);
