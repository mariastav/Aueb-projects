/* Find all the listings with price under $200 and show the squarefeet when this information is available 
Output: 11190 rows */
SELECT "Room".listing_id, "Room".square_feet, "Price".price
FROM "Price"
FULL OUTER JOIN "Room"
ON "Price".listing_id = "Room".listing_id
WHERE "Price".price < 200;

/* Find which listings have an exact location and the following coodinates.
Output: 11541*/
SELECT "Geolocation".properties_neighbourhood, "Location".is_location_exact, "Geolocation".geometry_coordinates_0_0_60_0,"Geolocation".geometry_coordinates_0_0_50_0
FROM "Geolocation"
FULL OUTER JOIN "Location"
ON "Location".neighbourhood_cleansed = "Geolocation".properties_neighbourhood;

/* Find all the cities that have more than 15 hosts. Cities with the most hosts are on top.
Output: 104 rows */
SELECT "Location".city, COUNT("Host".id) AS "numberOfHosts"
FROM "Host"
INNER JOIN "Location"
ON "Location".neighbourhood = "Host".neighbourhood
GROUP BY "Location".city
HAVING COUNT("Host".id)>15;

/* Find all listings that have a security deposit for $150 and are located in Plaka
Output: 44 rows */
SELECT "Room".listing_id, "Location".neighbourhood, "Room".security_deposit
FROM "Room"
INNER JOIN "Location"
ON "Location".listing_id = "Room".listing_id
WHERE "Room".security_deposit = '$150.00' AND "Location".neighbourhood = 'Plaka';

/* Find the listings with more than 100 reviews and show their price 
Output: 137 rows */
SELECT COUNT("Copy_Review".listing_id) AS "numberOfReviews", "Price".price
FROM "Copy_Review"
INNER JOIN "Price"
ON "Price".listing_id = "Copy_Review".listing_id
GROUP BY "Price".price
HAVING COUNT("Copy_Review".id) > 100
ORDER BY "numberOfReviews" DESC;

