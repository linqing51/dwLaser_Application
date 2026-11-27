# UI specification — 10.1-inch display, 1024 x 600

Dimensions below are unscaled CSS pixels on the device canvas. The English patient interface uses embedded Myriad Pro (Device Myriad), normal weight 400. Body, numeric and button letter spacing is 0 px; uppercase section labels use 1 px. Original parameter-screen graphics retain their existing appearance.

| Element | Font size / line height | Text color |
| --- | --- | --- |
| Section label and capacity | 14 / 20 px | #B6AFFF |
| Page or popup title | 26 / 32 px | #F4F4F5 |
| Patient name in list | 22 / 26 px | #F4F4F5 |
| ID, age and gender in list | 16 / 22 px | #C4C5CD |
| Treatment Records entry | 17 / 24 px | #C4BEFF |
| Primary and standard buttons | 18 / 24 px | #FFFFFF or #F4F4F5 |
| Delete Patient / Delete Treatment Record | 18 / 24 px | #F0B4A9 |
| Search input / placeholder | 18 / 24 px | #F4F4F5 / #BFC0C8 |
| Page number | 16 / 22 px | #C4C5CD |
| History date and numeric summary | 16 / 21 px | #D5D6DD |
| History mode, pulse and source device | 14 / 19 px | #BFC0C8 |
| Review numeric values | 28 / 34 px | #F4F4F5 |
| Save Record in review | 20 / 24 px | #FFFFFF |
| Confirmation body | 18 / 26 px | #C4C5CD |

- Patient list: 1024 x 600, 24 px horizontal padding, 52 px header, 44 px search input, five 72 px rows with 6 px gaps. Footer contains closing/selection actions and Previous/Page/Next on one line.
- History popup: 976 x 576 at x=24, y=12. Five 56 px record rows; fixed button pagination. No scrolling.
- Review card: 920 x 552 at x=52, y=24. Managing records uses the full canvas with the fixed history popup.
- Confirmation popup: 680 px wide, 24 px padding, inside the device canvas.
- Standard interactive controls are at least 44 px high; the review save button is at least 48 px high.
- Destructive confirmation buttons use #843E36 with white text. Background uses a dark grayscale radial gradient.
- USB Transfer appears only beside + New Patient on the patient list. The history popup opened from Manage Records has Back to Review and no USB entry.

Use the CSS as the implementation reference. Reuse fixed background, text and touch regions on the serial display; pagination updates content and record IDs without swipe animation frames. Final glyph rendering, touch operation and legibility require validation on the physical screen.
