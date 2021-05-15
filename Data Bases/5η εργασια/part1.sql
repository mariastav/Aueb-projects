/* Create table Amenity. */
CREATE TABLE "Amenity" (
amenity_id SERIAL PRIMARY KEY,
amenity_name varchar(550)
);

/* Make the right changes at Rooms's column "amenities" and then insert the values at Amenity's column "amenity_name". */
INSERT INTO "Amenity" (amenity_name)
SELECT DISTINCT TRIM(regexp_split_to_table(REPLACE(REPLACE(REPLACE(amenities, '{', ' '), '}', ' '), '"', ' '), ','))
FROM "Room";

/* Create table Amenity-Summary. */
CREATE TABLE "Amenity-Summary" AS
SELECT DISTINCT listing_id, TRIM(regexp_split_to_table(REPLACE(REPLACE(REPLACE(amenities, '{', ' '), '}', ' '), '"', ' '), ','))
FROM "Room";

/* Add amenity_id. */
ALTER TABLE "Amenity-Summary"
ADD amenity_id int;

/* Rename the needed columns. */
ALTER TABLE "Amenity-Summary"
RENAME COLUMN btrim TO amenity_name;

/* Add the values. */
UPDATE "Amenity-Summary" 
SET amenity_id = "Amenity".amenity_id
FROM "Amenity"
WHERE "Amenity-Summary".amenity_name = "Amenity".amenity_name;

/* Add the needed primary key in Room */
ALTER TABLE "Room"
ADD PRIMARY KEY (listing_id);

/* Add the foreign keys. */
ALTER TABLE "Amenity-Summary"
ADD FOREIGN KEY (listing_id) REFERENCES "Room"(listing_id);

ALTER TABLE "Amenity-Summary"
ADD FOREIGN KEY (amenity_id) REFERENCES "Amenity"(amenity_id);

/* Add the primary key. */
ALTER TABLE "Amenity-Summary"
ADD CONSTRAINT PK_amenity_summary PRIMARY KEY (listing_id, amenity_id);

/* Delete the necessary column. */
ALTER TABLE "Room"
DROP COLUMN amenities;
