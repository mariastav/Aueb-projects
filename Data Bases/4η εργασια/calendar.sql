/* Remove the unwanted symbols. */
UPDATE "Calendar"
SET price = REPLACE (REPLACE (price, '$', ''), ',' , '');

UPDATE "Calendar"
SET adjusted_price = REPLACE (REPLACE (price, '$', ''), ',', '');

/* Change the columns type into numeric. */
ALTER TABLE "Calendar"
ALTER COLUMN price TYPE INT USING price::numeric,
ALTER COLUMN adjusted_price TYPE INT USING price::numeric;
