# Validation — 16 November 2026

- 81 automated tests passed against the packaged source.
- TypeScript checking and portable production build passed.
- Tests cover patient limits, record limits, name length, pagination, selected-patient deletion, pending-review preservation, highlight dismissal, direct history management, confirmed whole-archive import, export-and-clear success and failure, and the two-patient/two-record USB B scenario.
- React static rendering checks cover English labels and five-row presentation. These are not browser layout tests.
- The entry HTML uses lang="en". Compiled JS/CSS and three original font files are embedded. Required image references resolve to packaged assets.
- No node_modules, development symlinks, English customer speech script or macOS metadata are included.
- ZIP integrity and file checksums were verified.
- Browser-by-browser visual inspection and physical device/USB/laser testing have not been completed. Existing browser file-access restrictions prevented automated visual acceptance in the working session.
