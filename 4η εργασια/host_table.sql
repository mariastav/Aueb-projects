/* Creating new table "Host". */
CREATE TABLE "Host" AS
SELECT DISTINCT "Listings".host_id, "Listings".host_url, "Listings".host_name, "Listings".host_since, "Listings".host_location, "Listings".host_about, "Listings".host_response_time, "Listings".host_response_rate, "Listings".host_acceptance_rate, "Listings".host_is_superhost, "Listings".host_thumbnail_url, "Listings".host_picture_url, "Listings".host_neighbourhood, "Listings".host_listings_count, "Listings".host_total_listings_count, "Listings".host_verifications, "Listings".host_has_profile_pic, "Listings".host_identity_verified, "Listings".calculated_host_listings_count
FROM "Listings";

/* Renaming columns on "Host". */
ALTER TABLE "Host" RENAME "host_id" TO "id";
ALTER TABLE "Host" RENAME "host_url" TO "url";
ALTER TABLE "Host" RENAME "host_name" TO "name";
ALTER TABLE "Host" RENAME "host_since" TO "since";
ALTER TABLE "Host" RENAME "host_location" TO "location";
ALTER TABLE "Host" RENAME "host_about" TO "about";
ALTER TABLE "Host" RENAME "host_response_time" TO "response_time";
ALTER TABLE "Host" RENAME "host_response_rate" TO "response_rate";
ALTER TABLE "Host" RENAME "host_acceptance_rate" TO "acceptance_rate";
ALTER TABLE "Host" RENAME "host_is_superhost" TO "is_superhost";
ALTER TABLE "Host" RENAME "host_thumbnail_url" TO "thumbnail_url";
ALTER TABLE "Host" RENAME "host_picture_url" TO "picture_url";
ALTER TABLE "Host" RENAME "host_neighbourhood" TO "neighbourhood";
ALTER TABLE "Host" RENAME "host_listings_count" TO "listings_count";
ALTER TABLE "Host" RENAME "host_total_listings_count" TO "total_listings_count";
ALTER TABLE "Host" RENAME "host_verifications" TO "verifications";
ALTER TABLE "Host" RENAME "host_has_profile_pic" TO "has_profile_pic";
ALTER TABLE "Host" RENAME "host_identity_verified" TO "identity_verified";
ALTER TABLE "Host" RENAME "calculated_host_listings_count" TO "calculated_listings_count";

/* Dropping the columns that aren't needed anymore on "Copy_Listings" */
ALTER TABLE "Copy_Listings" DROP COLUMN host_url;
ALTER TABLE "Copy_Listings" DROP COLUMN host_name;
ALTER TABLE "Copy_Listings" DROP COLUMN host_since;
ALTER TABLE "Copy_Listings" DROP COLUMN host_location;
ALTER TABLE "Copy_Listings" DROP COLUMN host_about;
ALTER TABLE "Copy_Listings" DROP COLUMN host_response_time;
ALTER TABLE "Copy_Listings" DROP COLUMN host_response_rate;
ALTER TABLE "Copy_Listings" DROP COLUMN host_acceptance_rate;
ALTER TABLE "Copy_Listings" DROP COLUMN host_is_superhost;
ALTER TABLE "Copy_Listings" DROP COLUMN host_thumbnail_url;
ALTER TABLE "Copy_Listings" DROP COLUMN host_picture_url;
ALTER TABLE "Copy_Listings" DROP COLUMN host_neighbourhood;
ALTER TABLE "Copy_Listings" DROP COLUMN host_listings_count;
ALTER TABLE "Copy_Listings" DROP COLUMN host_total_listings_count;
ALTER TABLE "Copy_Listings" DROP COLUMN host_verifications;
ALTER TABLE "Copy_Listings" DROP COLUMN host_has_profile_pic;
ALTER TABLE "Copy_Listings" DROP COLUMN host_identity_verified;
ALTER TABLE "Copy_Listings" DROP COLUMN calculated_host_listings_count;

/* Setting primary and foreign keys where needed. */
ALTER TABLE "Host" ADD PRIMARY KEY ("id");
ALTER TABLE "Copy_Listings" ADD FOREIGN KEY ("host_id") REFERENCES "Host"(id);