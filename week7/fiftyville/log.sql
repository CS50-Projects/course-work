-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = "Chamberlin Street";

Theft of duck happened at 10:15 at the courthouse
Interviews conducted same day with three witnesses
Each interview mentions the courthouse

SELECT * FROM interviews WHERE day = 28 AND month = 7;

Ruth - within 10 minute of the theft, the thief got into a car in the courthouse parking lot and drove away. Security footage from the lot will show cars leaving around that time
Eugene - recognized the thief. Saw the thief at an ATM on Fifer Street withdrawing some money BEFORE he arrived at the courthouse.
Raymond - as the thief was leaving the courthouse, they called someone for less than a minute. They said they were going to take the earliest flight out of FiftyVille tomrorow (July 29th). The thief then asked the other person to buy the ticket

Possible license places + matches
SELECT * FROM people WHERE license_plate = "";
10:16 - 5P2BI95 - 221103 | Patrick - (725) 555-4692 | 2963008352 |
10:18 - 94KL13X - 686048 | Ernest | (367) 555-5533 | 5773159633 |
10:18 - 6P58WS2 - 243696 | Amber | (301) 555-4174 | 7526138472 |
10:19 - 4328GD8 - 467400 | Danielle | (389) 555-5198 | 8496433585 |
10:20 - G412CB7 - 398010 | Roger | (130) 555-0289 | 1695452385 |
10:21 - L93JTIZ - 396669 | Elizabeth | (829) 555-5269 | 7049073643 |
10:23 - 322W7JE - 514354 | Russell | (770) 555-1861 | 3592750733 |
10:23 - 0NTHK55 - 560886 | Evelyn | (499) 555-9472 | 8294398571 |

Checking out the withdrawals for that day, though none have times
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location  = "Fifer Street";
id, account number, year, month, date, location, type, amount
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48 - Danielle
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20 - Bobby
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60 - Madison
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50 - Ernest
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80 - Roy
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20 - Elizabeth
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30 - Victoria
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35 - Russell

Checking phone calls on that day that were under a minute in length
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60;
id, caller, receiver, year, month, day, duration
221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

Suspects:

Ernest - called Berthold
Roger - Called Jack
Russell - Called Philip
Evelyn - Called Larry
Evelyn - Called Melissa

Potential thiefs: Russell, Ernest
Potential accomplice: Berthold, Philip

Earliest flights out on the 29th:
id, origin_airport_id, destination_airport_id, year, month, day, hour
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 - Going to Heathrow
43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 - Going to O'Hare International Airport


Check who bought tickets to either of those flights:
SELECT * FROM passengers WHERE flight_id = 36;
flight_id, passport_number, seat

36 | 7214083635 | 2A -
36 | 1695452385 | 3B -
36 | 5773159633 | 4A -
36 | 1540955065 | 5C -
36 | 8294398571 | 6C -
36 | 1988161715 | 6D -
36 | 9878712108 | 7A -
36 | 8496433585 | 7B -

SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
Bobby
Roger
Madison
Danielle
Evelyn
Edward
Ernest
Doris

SELECT * FROM passengers WHERE flight_id = 43;
43 | 7597790505 | 7B
43 | 6128131458 | 8A
43 | 6264773605 | 9A
43 | 3642612721 | 2C
43 | 4356447308 | 3B
43 | 7441135547 | 4A

Thief - Ernest
Accomplice - Berthold
Airport - Heathrow


