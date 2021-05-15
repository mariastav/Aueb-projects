/* Creates the index for the query 1:
EXPLAIN ANALYZE SELECT "Host".id, COUNT(*) FROM "Copy_Listing", "Host"
WHERE "Host".id = "Copy_Listing".host_id
GROUP BY "Host".id;
*/
CREATE INDEX listing_idx
ON "Copy_Listing" (host_id);

/* Creates the index for the query 2:
EXPLAIN ANALYZE SELECT id, price FROM "Copy_Listing", "Price"
WHERE guests_included > 5 AND price > 40;
*/
CREATE INDEX price_idx
ON "Price" (guests_included, price) WHERE (guests_included >5 AND price > 40);

/* Creates the index for the query 5.1:
EXPLAIN ANALYZE SELECT "Room".listing_id, "Room".square_feet, "Price".price
FROM "Price"
FULL OUTER JOIN "Room"
ON "Price".listing_id = "Room".listing_id
WHERE "Price".price < 200;
*/
CREATE INDEX room_idx
ON "Room" (listing_id, square_feet);

/* Creates the index for the query 5.2:
EXPLAIN ANALYZE SELECT "Geolocation".properties_neighbourhood, "Location".is_location_exact, "Geolocation".geometry_coordinates_0_0_60_0,"Geolocation".geometry_coordinates_0_0_50_0
FROM "Geolocation"
FULL OUTER JOIN "Location"
ON "Location".neighbourhood_cleansed = "Geolocation".properties_neighbourhood;
*/
CREATE INDEX geolocation_idx
ON "Geolocation" (properties_neighbourhood);
CREATE INDEX location_idx
ON "Location" (neighbourhood_cleansed);

/* Creates the index for the query 5.3:
EXPLAIN ANALYZE SELECT "Location".city, COUNT("Host".id) AS "numberOfHosts"
FROM "Host"
INNER JOIN "Location"
ON "Location".neighbourhood = "Host".neighbourhood
GROUP BY "Location".city
HAVING COUNT("Host".id)>15;
*/
CREATE INDEX location_idx2
ON "Location" (neighbourhood);
CREATE INDEX host_idx
ON "Host" (id, neighbourhood);

/* Creates the indexes for the query 5.4:
EXPLAIN ANALYZE SELECT "Room".listing_id, "Location".neighbourhood, "Room".security_deposit
FROM "Room"
INNER JOIN "Location"
ON "Location".listing_id = "Room".listing_id
WHERE "Room".security_deposit = '$150.00' AND "Location".neighbourhood = 'Plaka';
*/
CREATE INDEX room_idx2
ON "Room" (listing_id, security_deposit)
WHERE (security_deposit = '$150.00');

CREATE INDEX location_idx2
ON "Location" (neighbourhood) WHERE (neighbourhood = 'Plaka');

/* Creates the index for the query 5.5:
EXPLAIN ANALYZE SELECT COUNT("Copy_Review".listing_id) AS "numberOfReviews", "Price".price
FROM "Copy_Review"
INNER JOIN "Price"
ON "Price".listing_id = "Copy_Review".listing_id
GROUP BY "Price".price
HAVING COUNT("Copy_Review".id) > 100
ORDER BY "numberOfReviews" DESC;
*/
CREATE INDEX price_idx2
ON "Price" (listing_id, price);

CREATE INDEX copyReview_idx
ON "Copy_Review" (listing_id);


