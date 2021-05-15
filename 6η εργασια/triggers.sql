/* Creates a trigger, that triggers when listing is inserted in the table Listing, or removed from it.
And updates the column host_listings_count at table Host depending on the command.
*/

CREATE OR REPLACE FUNCTION update_host_listings_count()
	RETURNS trigger AS
$BODY$
BEGIN
	IF (TG_OP = 'INSERT') THEN
		UPDATE "Copy_Host"
		SET listings_count = COALESCE(listings_count, 0) + 1
		WHERE NEW.host_id = "Copy_Host".id;
		RETURN NEW;
	ELSIF (TG_OP = 'DELETE') THEN
		UPDATE "Copy_Host"
		SET listings_count = COALESCE(listings_count, 0) - 1
		WHERE OLD.host_id = "Copy_Host".id;
		RETURN OLD;
	END IF;	
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER sum_of_listings
	AFTER INSERT OR DELETE
	ON "Copy_Listings"
	FOR EACH ROW
	EXECUTE PROCEDURE update_host_listings_count();

/* Creates a trigger, that triggers when a review is inserted in the table Review, or removed from it.
And updates the column number_of_reviews at table Listing depending on the command.
*/

CREATE OR REPLACE FUNCTION update_number_of_reviews()
RETURNS trigger AS
$BODY$
BEGIN
  IF (TG_OP = 'INSERT') THEN
    UPDATE "Copy_Listings" SET number_of_reviews = COALESCE(number_of_reviews, 0) + 1
    WHERE NEW.listing_id = "Copy_Listings".id;
    RETURN NEW;
  ELSIF (TG_OP = 'DELETE') THEN
    UPDATE "Copy_Listings" SET number_of_reviews = COALESCE(number_of_reviews, 0) - 1
    WHERE OLD.listing_id = "Copy_Listings".id;
    RETURN OLD;
  END IF;
END;
$BODY$
LANGUAGE plpgsql;
 
CREATE TRIGGER review_trigger
AFTER INSERT OR DELETE ON "Copy_Reviews"
  FOR EACH ROW EXECUTE PROCEDURE update_number_of_reviews();
