# Waste collection

When the next bin goes out, from a calendar in Home Assistant: on a tile, in the top bar the day before, and on a card
with the collections of the coming four weeks.

The tile shows what goes out (paper, garden waste, plastic) with its colour, when ("Tomorrow", "In 3 days") as large as
the tile allows, and the date under it. A tap opens the card. The top bar says "Tomorrow: Paper" from the day before,
or as many days ahead as you set on the screen.

## Set up

1. Have a calendar with the collection days in Home Assistant. [Waste Collection Schedule](https://github.com/mampfes/hacs_waste_collection_schedule)
   and Afvalwijzer make one for most councils; a Local Calendar with the days typed in works too.
2. In Tessera, open **Plugins**, choose **Waste collection**, tick your screens, and choose the calendar under
   **Waste calendar**. Each screen builds once with the plugin.
3. Put the tile **Next collection** on a page and choose the calendar in its inspector.
4. Optional: add **Next collection** to a page's top bar (Top bar, Add, From plugins).
5. Optional: a sensor tile of your waste integration can open the card too: set its tap to **Show coming collections**.

## On the screen

Hold the top bar, then **Settings**, **Plugins**, **Waste collection**:

- **In the top bar**: whether the top bar says it at all.
- **Days ahead**: from how many days before a collection the top bar says it (0 is the day itself, 1 the day before).
- **Coming collections**: opens the card.

Both settings are entities of the screen in Home Assistant too ("Waste in top bar", "Waste days ahead"), so an automation
can change them, and the editor shows them in the plugin's details on the screen's Plugins tab.

## Good to know

- The colours follow the words calendars use: paper and cardboard blue, garden and food waste green, plastic and
  packaging amber, glass and metal purple, anything else grey. Norwegian, Dutch and English words work. Glass and
  metal packaging are recognised before general packaging. The calendar's names stay as they are.
- The card asks Home Assistant for the coming events through Tessera (`calendar.get_events`); the screen reads the
  calendar's next event itself for the top bar.
- The top bar item shows only while the next collection is within the days you set under **Waste days ahead**.
- Works on every board, the CYD included.

## ROAF (Norway)

1. In Home Assistant, install **Waste Collection Schedule** from HACS, or from **Settings, Marketplace** on versions
   that include it. Add the integration and select Norway and ROAF (Min Renovasjon, source `minrenovasjon_no`).
2. Enter your street name, house number, street code and municipality number. Use the current values for your address,
   not the example values in the source's documentation. [The source's instructions](https://github.com/mampfes/hacs_waste_collection_schedule/blob/master/doc/source/minrenovasjon_no.md)
   explain how to find `street_code` (`adressekode`) and `county_id` (`kommunenummer`) with the Norwegian address service.
3. Check that its calendar has the same next collection dates and waste types as ROAF's collection calendar. Select
   this same calendar both when adding the plugin and in the tile's inspector.
4. Add the plugin's top bar item and leave **Days ahead** at 1 for a reminder the day before and on collection day.
   It is a top bar reminder, not a phone notification or an automatic wake-up.
5. For Norwegian words, use a Tessera app and firmware that include Bokmål (`nb`), choose it under **Language & region**,
   and rebuild the screen. This plugin alone adds Norwegian waste colours on an English screen, but does not add a
   language to Tessera's language selector. This fork's companion changes are on
   [Tessera's Bokmål development branch](https://github.com/hasandem/homeassistant_espscreen/tree/dev).

The address stays in Home Assistant. It is not a plugin input and does not belong in this repository. ROAF dates are
fetched by the integration, so no ROAF connection or new network permission is added to the screen.

## Install this fork for testing

1. In Tessera, open **Plugins**, then **Add with a link**.
2. Paste [the plugin folder on this fork's dev branch](https://github.com/hasandem/tessera-plugins/tree/dev/plugins/waste_collection).
   If the dialog asks how to follow it, choose **Test a branch** and enter `dev`.
3. If a screen already has Waste collection from another origin, switch its origin in the plugin's details. The id
   stays `waste_collection`, so its layout tiles can be kept. Check the chosen calendar before installing.
4. Choose the target screen and install. This builds its firmware; adding the link alone does not update the screen.

No GitHub release, tag or Marketplace submission is needed. A newer commit on the branch appears as an update after
the app checks GitHub (at most once an hour). Installing that update builds the screen again.

## Checks

`python3 tools/check.py plugins/waste_collection` checks the manifest and translations. The standalone colour test
uses the same classification as the firmware:

```sh
c++ -std=c++17 plugins/waste_collection/tests/test_waste_kind.cpp -o /tmp/test-waste-kind
/tmp/test-waste-kind
```

On a real screen, check today, tomorrow, no planned collection, an unavailable calendar, light and dark themes, and
returning to the page. A card's four-week range can only show the rows that fit; multiple collections on one day keep
their own rows when Home Assistant returns separate events. Builds and these host checks do not prove a physical test.

## How it works

- `tessera-plugin.yaml`: a tile that belongs to a calendar entity (with its `message` and `start_time`), a card, a tap
  action for sensor tiles, a top bar item, and the one Home Assistant command it may ask: `calendar.get_events`.
- `plugin.yaml`: two `homeassistant` text sensors that read the chosen calendar for the top bar, and the two settings as
  a template switch and number.
- `components/waste_collection/`: the tile, the card, the tap action, the top bar item and the settings rows.
