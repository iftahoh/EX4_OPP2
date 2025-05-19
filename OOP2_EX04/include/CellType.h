#pragma once
enum class CellType {
    OPEN,        // שטח פתוח (שחור)
    CLOSED,      // שטח סגור (ירוק) 
    TRAIL,       // קו שהשחקן יוצר (ורוד)
    BORDER       // גבול המסך
};