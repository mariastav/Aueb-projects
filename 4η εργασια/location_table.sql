/* Creating new table "Location". */
CREATE TABLE "Location" AS
SELECT id, street, neighbourhood, neighbourhood_cleansed, city, state,
zipcode, market, smart_location, country_code, country, latitude, longitude,
is_location_exact FROM "Listings";

/* Renaming the needed column on "Location". */
ALTER TABLE "Location"
RENAME COLUMN "id" TO "listing_id";

/* Delete the needed constraint key */
ALTER TABLE "Copy_Listing" DROP CONSTRAINT "Copy_Listings_neighbourhood_cleansed_fkey";

/* Deletes the copied columns */
ALTER TABLE "Copy_Listings" DROP COLUMN street;
ALTER TABLE "Copy_Listings" DROP COLUMN neighbourhood;
ALTER TABLE "Copy_Listings" DROP COLUMN neighbourhood_cleansed;
ALTER TABLE "Copy_Listings" DROP COLUMN city;
ALTER TABLE "Copy_Listings" DROP COLUMN state;
ALTER TABLE "Copy_Listings" DROP COLUMN zipcode;
ALTER TABLE "Copy_Listings" DROP COLUMN market;
ALTER TABLE "Copy_Listings" DROP COLUMN smart_location;
ALTER TABLE "Copy_Listings" DROP COLUMN country_code;
ALTER TABLE "Copy_Listings" DROP COLUMN country;
ALTER TABLE "Copy_Listings" DROP COLUMN latitude;
ALTER TABLE "Copy_Listings" DROP COLUMN longitude;
ALTER TABLE "Copy_Listings" DROP COLUMN is_location_exact;

/* Adds foreign key */
ALTER TABLE "Location"
ADD FOREIGN KEY (listing_id) REFERENCES "Listings"(id);