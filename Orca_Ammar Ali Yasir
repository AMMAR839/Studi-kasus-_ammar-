START

// Inisialisasi
Initialize sensors (visual/camera or sonar)
Calibrate sensors

// Deteksi Tempat Drop
WHILE True
    // Ambil citra dari sensor visual atau data dari sonar
    image = CaptureImage()  // Jika menggunakan kamera
    sonarData = CaptureSonarData()  // Jika menggunakan sonar
    
    // Proses citra atau data sonar
    IF UsingCamera THEN
        detectedCircle = DetectRedCircle(image)
        IF detectedCircle IS NOT NULL THEN
            placeDrop = detectedCircle
            BREAK
        ENDIF
    ELSE IF UsingSonar THEN
        detectedCircle = DetectCircleFromSonar(sonarData)
        IF detectedCircle IS NOT NULL THEN
            placeDrop = detectedCircle
            BREAK
        ENDIF
    ENDIF
ENDWHILE

// Tentukan posisi tempat drop
center = placeDrop.center
radius = placeDrop.radius

// Pendekatan ke Tempat Drop
NavigateTo(center)

// Jatuhkan Payload
IF AtTargetPosition(center) THEN
    ReleasePayload()
ENDIF

// Verifikasi Payload Jatuh di Tempat Drop
WHILE True
    // Ambil citra dari sensor visual atau data dari sonar
    image = CaptureImage()  // Jika menggunakan kamera
    sonarData = CaptureSonarData()  // Jika menggunakan sonar
    
    // Verifikasi posisi payload
    IF UsingCamera THEN
        payloadPosition = DetectPayloadPosition(image)
        IF IsPayloadInCircle(payloadPosition, center, radius) THEN
            verificationStatus = TRUE
            BREAK
        ELSE
            verificationStatus = FALSE
        ENDIF
    ELSE IF UsingSonar THEN
        payloadPosition = DetectPayloadFromSonar(sonarData)
        IF IsPayloadInCircle(payloadPosition, center, radius) THEN
            verificationStatus = TRUE
            BREAK
        ELSE
            verificationStatus = FALSE
        ENDIF
    ENDIF
ENDWHILE

// Naik ke Permukaan
IF verificationStatus THEN
    PlanAscendPath()
    AscendToSurface()
ENDIF

END
