# Final English engineering handoff

Packaged 16 November 2026 from the latest confirmed implementation. This package does not change the interface behavior delivered on 14 November.

## Patient storage and limits

- Save patient demographics and treatment records on the device. USB is used for explicit transfer.
- Maximum 380 patients per device, 10 saved treatment records per patient, and 18 characters per name, including spaces. Name is required; age and gender are optional.
- Reaching a limit blocks new data. No automatic removal of the oldest patient or record.
- Display IDs (AR 0001, etc.) follow the device archive's patient creation counter, not list position or treatment count. Deletion and export do not reset that counter. Import preserves incoming IDs and uses the larger existing/incoming counter. Internal UIDs distinguish independently created patients with equal display IDs.

## Parameter screen and treatment

The patient icon is highlighted on first entering the parameter screen after startup. Starting a parameter adjustment or opening Patient Info dismisses the highlight immediately. This includes touching a slider without changing its value, selecting the current mode, and attempting adjustment at a boundary. Ready also dismisses it. Returning to the screen does not rearm the hint; restarting does.

Pre-treatment patient selection or registration is optional. The parameter and treatment screens display the selected name and ID, or No patient selected.

Every Standby ends the current treatment session. If output occurred, output stops first, the interface returns to an inert parameter-screen background, and the review card opens. The 450 ms animation is a visual sequence, not confirmation of physical hardware safety. With zero output, no treatment record is created.

Review must end with successful Save Record or explicitly confirmed Discard Record. The treatment-end timestamp is preserved. Saving or discarding clears the patient association for the next treatment. Hardware must independently verify that laser emission is disabled before displaying review.

## Lists, history and deletion

Patient lists have five rows per page. Treatment history is a separate popup with five complete rows per page; ten records use two pages. Navigation uses Previous and Next, never swiping or inline expansion.

Select Patient and Delete Patient are side by side in each patient row. A selected patient can be deleted after confirmation. Deletion removes that patient's saved records and clears the association. If a treatment is still unsaved, its snapshot remains and the user must select or register a patient again. Failed deletion keeps the original data and association.

Delete Treatment Record removes only the identified saved record. Confirmation retains the warning that the operation cannot be undone, without the extra USB-backup sentence.

At the ten-record limit, Manage Records opens the current patient's history directly. After deleting an old record, Back to Review returns directly to the pending treatment. When creating a new patient at the 380-patient limit, Manage Records instead opens the patient list for cleanup.

## USB transfer — final rules

USB Transfer appears only on the patient-list page beside + New Patient. There is no USB Transfer button in treatment history.

Export and Clear Device requires explicit confirmation. It exports all saved patients and treatment records to the selected simulated USB, replacing an existing backup after confirmation. On success, the active device's saved archive is cleared and its patient selection is removed. Other devices and the other USB remain unchanged. The patient-number counter is retained. A failed export preserves the previous device data and USB backup.

An unsaved treatment is excluded from export. Its snapshot remains in memory after export; its old saved-patient association is cleared, so the doctor must select or register a patient before saving. A newly entered, unsaved patient form is retained.

Import from USB validates version, patient and record limits, fields and IDs before replacing the complete device archive. The confirmation shows source and destination counts. Canceling or failing import preserves the original archive. Import is not a merge and is not restricted by source device serial number. Treatment identity, original timestamp and source serial are retained.

During unresolved treatment, import, device switching and restarting are blocked. Exporting saved data remains available from the patient list (Back to Review > Change Patient > USB Transfer).

For firmware, write and verify the USB archive before clearing device storage. Implement transaction recovery and power-loss handling for the real storage hardware; the atomic in-memory simulation is not a physical storage implementation.

## Demonstration scenarios

### Two-patient USB B replacement

1. Start a fresh page. Device A has ten patients; Ankita / AR 0002 has ten history records.
2. Select USB B using the Simulated drive control below the canvas.
3. Open the patient list, USB Transfer, then Import from USB.
4. Confirm Replace and Import. The patient list now contains Emma Wilson and Daniel Chen, each with one treatment record. The original device patients have been replaced.
5. Cancel the confirmation instead to demonstrate that the original data remains.

USB B begins with this sample backup on every fresh page load. Exporting to USB B deliberately replaces it; refresh the page to reset the full demonstration.

### Record limit and cleanup

Select Ankita / AR 0002. Enter Ready, hold the simulated footswitch, then select Standby. Save Record reports the ten-record limit. Manage Records opens this patient's history directly. Delete an old record, return to review, and save the pending treatment.

### Export and failure

From the patient list, open USB Transfer and export to USB A. Confirm Export and Clear Device. The device patient count becomes zero, and the USB backup contains the previous saved archive. Import it to restore it, or switch devices and import it to demonstrate portability. Simulate USB write failure or device storage failure to verify that failed export retains original data; clear the failure and retry.

## Source and build

- app/page.tsx: screens, fixed history popup, confirmations and navigation.
- app/globals.css and app/fonts: styles and embedded Myriad Pro fonts.
- lib/demo-model.mjs: treatment, device archives, capacity checks and USB transfer.
- lib/i18n.mjs: localized display strings. This package's entry uses lang="en"; stored enums, IDs and patient names are not translated.
- tests/: automated behavior and static-rendering checks.

For development, use Node.js 22.13 or newer and install dependencies using pnpm-lock.yaml. node_modules is intentionally excluded. Development dependency installation may require internet access; viewing the prebuilt index.html does not.

Run npm test, npm run typecheck, then npm run build. The build generates a portable dist/index.html with JS/CSS/fonts embedded; keep dist/assets beside it. The older dated packaging script in source preserves its historical output names; this final English handoff has a separate dated delivery folder.

This is an interface demonstration, not firmware. Device A/B/C and USB A/B are independent in-memory simulations. No physical USB, laser hardware, browser persistent storage or remote data upload is used. Restart preserves saved simulated media; page reload resets all simulated data.
