/* Find the available rentings from 2021-02-09 till 2021-02-19 that costs between 100$-300$.
   Output: 9589 rows */
SELECT DISTINCT "Listings-Summary".name, "Calendar".date, "Listings-Summary".price, "Calendar".available
FROM "Listings-Summary"
INNER JOIN "Calendar"
ON "Calendar".listing_id = "Listings-Summary".id
WHERE ("Listings-Summary".price BETWEEN 100 AND 300) AND ("Calendar".date BETWEEN '2021-02-09' AND '2021-02-19') AND available = true
ORDER BY "Listings-Summary".price ASC;

/* Find the first 100 available airbnbs on March 2020 from a host that his/her name starts with "E".
   Output 100 rows */
SELECT DISTINCT "Listings".host_id, "Listings".host_name, "Listings".id, "Listings".name
FROM "Listings"
INNER JOIN "Calendar"
ON "Listings".id = "Calendar".listing_id
WHERE ("Listings".host_name LIKE 'E%') AND ("Calendar".available = true) AND ("Calendar".date BETWEEN '2020-03-01' AND '2020-03-31')
ORDER BY "Listings".id ASC
LIMIT 100;

/* Calculate the average price of the listings in each neighbourhood.
   Output 45 rows */
SELECT "Neighbourhoods".neighbourhood, AVG("Listings-Summary".price)
FROM "Neighbourhoods"
INNER JOIN "Listings-Summary"
ON "Listings-Summary".neighbourhood = "Neighbourhoods".neighbourhood
GROUP BY "Neighbourhoods".neighbourhood;

/* Find the geolocation type for each listing.
   Output: 11541 rows */
SELECT "Listings".id, "Listings".neighbourhood, "Listings".street, "Geolocation".type
FROM "Listings"
INNER JOIN "Geolocation"
ON "Listings".neighbourhood_cleansed = "Geolocation".properties_neighbourhood
ORDER BY "Listings".id;

/* Find the reviews for the most commented renting.
   Output: 708 rows */
SELECT "Listings".id, "Listings".name, "Reviews".comments
FROM "Reviews"
INNER JOIN "Listings"
ON "Reviews".listing_id = "Listings".id
WHERE number_of_reviews = (SELECT MAX(number_of_reviews) FROM "Listings")
ORDER BY "Reviews".date DESC;

/* Find the first 100 reviews of the rentings that have air-conditioning in their amenities.
   Output: 100 rows */
SELECT DISTINCT "Listings".id,"Listings".amenities, "Reviews".id, "Reviews".comments
FROM "Listings"
INNER JOIN "Reviews"
ON "Listings".id = "Reviews".listing_id
WHERE "Listings".amenities LIKE '%Air conditioning%'
LIMIT 100;

/* Calculate how many types of rentings are available.
   Output: 26 rows */
SELECT "Listings".property_type, COUNT ("Listings".has_availability = 't')
FROM "Listings"
INNER JOIN "Listings" as b
ON "Listings".id = b.id
GROUP BY "Listings".property_type
ORDER BY count DESC;

/* Find all rentings which are located in Plaka and are available on 26-04-2020.
   Output: 1087 rows */
SELECT DISTINCT "Listings".id, "Listings".bedrooms, "Calendar".price
FROM "Listings"
INNER JOIN "Calendar"
ON "Listings".id = "Calendar".listing_id
WHERE "Listings".neighbourhood = 'Plaka' AND "Calendar".date = '2020-04-26' AND "Calendar".available = 't';

/* Find the minimum number of bedrooms and bathrooms a listing between 100 and 200sqr feet has.
   Output: 1 rows */
SELECT MIN(bedrooms), MIN(bathrooms)
FROM "Listings"
WHERE square_feet BETWEEN '100' AND '200';

/* Find all the available rentings that have reviews from at least year 2020.
   Output: 21877 rows */
SELECT DISTINCT "Listings".id, "Reviews".date, "Listings".review_scores_rating
FROM "Listings"
INNER JOIN "Reviews"
ON "Listings".id = "Reviews".listing_id
WHERE "Listings".has_availability = 't' AND "Reviews".date > '2020-01-01'
ORDER BY "Reviews".date DESC;

/* Find all the hosts that are reviewers, those that aren't and the reviewers that aren't hosts.(Note that if someone has an airbnb account, they'll use the same one to list rentings and to post reviews, so if a host has made a review his host_id = reviewer_id. If he hasn't made a review yet but has listed a rent, he will have a host_id but his reviewer_id = null until he posts a review, in that case the host_id = reviewer_id)
   Output: 371696 rows */
SELECT DISTINCT "Listings".host_id, "Listings".host_name, "Reviews".reviewer_id, "Reviews".reviewer_name
FROM "Listings"
FULL OUTER JOIN "Reviews"
ON "Listings".host_id = "Reviews".reviewer_id;

/* Find for each renting, if a reviewer exist. 
   Output: 410981 rows */
SELECT DISTINCT "Listings".id, "Reviews".reviewer_id, "Reviews".reviewer_name
FROM "Reviews"
RIGHT OUTER JOIN "Listings" ON "Reviews".listing_id = "Listings".id;